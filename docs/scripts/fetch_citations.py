#!/usr/bin/env python3
"""Refresh HeRo paper metadata and incoming citations.

Uses OpenAlex (https://api.openalex.org), not Google Scholar.
Scholar has no public API and blocks scrapers; OpenAlex is the dataset
that can run unattended on GitHub Actions.

Seed works are the HeRo platform papers plus the two swarm papers
already listed on the site. Citation counts and citing works are
whatever OpenAlex has on the day the script runs.
"""
from __future__ import print_function

import json
import os
import sys
import time
from datetime import datetime, timezone
from urllib.parse import quote
from urllib.request import Request, urlopen

SEEDS = [
    {
        "key": "hero2",
        "doi": "10.1007/s10514-023-10100-0",
        "role": "platform",
        "cite_as": True,
    },
    {
        "key": "hero2017",
        "doi": "10.1109/sbr-lars-r.2017.8215317",
        "role": "platform",
        "cite_as": True,
        "fallback_search": "HeRo open platform robotics research education Rezeck",
    },
    {
        "key": "chemistry",
        "doi": "10.1109/LRA.2022.3190638",
        "role": "related",
        "cite_as": False,
    },
    {
        "key": "transport",
        "doi": "10.1109/IROS51168.2021.9635928",
        "role": "related",
        "cite_as": False,
    },
]

MAILTO = os.environ.get("OPENALEX_MAILTO", "rezeck@dcc.ufmg.br")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "assets", "data", "citations.json")
UA = "hero_common citation bot (%s)" % MAILTO


def get(url):
    req = Request(url, headers={"User-Agent": UA})
    with urlopen(req, timeout=40) as resp:
        return json.loads(resp.read().decode("utf-8"))


def authors_of(work):
    names = []
    for auth in work.get("authorships") or []:
        author = auth.get("author") or {}
        name = author.get("display_name")
        if name:
            names.append(name)
    return names


def compact(work):
    loc = ((work.get("primary_location") or {}).get("source") or {}).get("display_name")
    doi = None
    if work.get("doi"):
        doi = work["doi"].replace("https://doi.org/", "")
    return {
        "id": work.get("id"),
        "doi": doi,
        "title": work.get("title") or work.get("display_name"),
        "year": work.get("publication_year"),
        "venue": loc,
        "authors": authors_of(work),
        "cited_by_count": work.get("cited_by_count"),
        "url": (work.get("primary_location") or {}).get("landing_page_url")
        or ("https://doi.org/%s" % doi if doi else work.get("id")),
    }


def find_work(seed):
    doi = seed.get("doi")
    if doi:
        try:
            return get("https://api.openalex.org/works/doi:%s?mailto=%s" % (quote(doi), MAILTO))
        except Exception as exc:
            print("DOI miss %s (%s)" % (doi, exc), file=sys.stderr)
    query = seed.get("fallback_search")
    if not query:
        return None
    data = get(
        "https://api.openalex.org/works?search=%s&per_page=5&mailto=%s"
        % (quote(query), MAILTO)
    )
    results = data.get("results") or []
    return results[0] if results else None


def citing_works_openalex(openalex_id, limit=80):
    short = openalex_id.rsplit("/", 1)[-1]
    cited = []
    cursor = "*"
    pages = 0
    while len(cited) < limit and pages < 6:
        url = (
            "https://api.openalex.org/works?filter=cites:%s&per_page=50"
            "&cursor=%s&mailto=%s" % (short, quote(cursor), MAILTO)
        )
        data = get(url)
        pages += 1
        for work in data.get("results") or []:
            cited.append(compact(work))
            if len(cited) >= limit:
                break
        cursor = (data.get("meta") or {}).get("next_cursor")
        if not cursor:
            break
        time.sleep(0.15)
    return cited


def citing_works_s2(doi, limit=80):
    url = (
        "https://api.semanticscholar.org/graph/v1/paper/DOI:%s"
        "?fields=title,citationCount,citations.title,citations.year,"
        "citations.citationCount,citations.authors,citations.externalIds,"
        "citations.url,citations.venue"
        "&limit=%d" % (quote(doi), limit)
    )
    try:
        data = get(url)
    except Exception as exc:
        print("  Semantic Scholar miss %s (%s)" % (doi, exc), file=sys.stderr)
        return None, []
    cited = []
    for work in data.get("citations") or []:
        ext = work.get("externalIds") or {}
        authors = [a.get("name") for a in (work.get("authors") or []) if a.get("name")]
        doi_c = ext.get("DOI")
        cited.append(
            {
                "id": work.get("paperId"),
                "doi": doi_c,
                "title": work.get("title"),
                "year": work.get("year"),
                "venue": work.get("venue"),
                "authors": authors,
                "cited_by_count": work.get("citationCount"),
                "url": work.get("url")
                or ("https://doi.org/%s" % doi_c if doi_c else None),
            }
        )
    return data.get("citationCount"), cited


def main():
    works = []
    incoming = []
    seen = set()
    for seed in SEEDS:
        work = find_work(seed)
        time.sleep(0.2)
        if not work:
            works.append({"key": seed["key"], "error": "not found", "doi": seed.get("doi")})
            continue
        item = compact(work)
        item["key"] = seed["key"]
        item["role"] = seed["role"]
        item["cite_as"] = seed["cite_as"]
        item["openalex"] = work.get("id")
        print("  OpenAlex:", item.get("title"), "cited_by", item.get("cited_by_count"))
        s2_count, s2_cites = citing_works_s2(item["doi"], 80) if item.get("doi") else (None, [])
        if s2_count is not None:
            item["semantic_scholar_citations"] = s2_count
        works.append(item)
        extra = s2_cites or citing_works_openalex(work["id"])
        if seed["role"] == "platform":
            for cite in extra:
                cid = cite.get("doi") or cite.get("id")
                if not cid or cid in seen:
                    continue
                seen.add(cid)
                incoming.append(cite)

    incoming.sort(key=lambda w: (w.get("cited_by_count") or 0, w.get("year") or 0), reverse=True)
    payload = {
        "source": "OpenAlex",
        "source_url": "https://openalex.org",
        "generated_at": datetime.now(timezone.utc).isoformat(),
        "note": "OpenAlex for metadata; Semantic Scholar for citing lists when available. Not Google Scholar.",
        "seeds": works,
        "citing": incoming,
    }
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(payload, fh, indent=2, ensure_ascii=False)
        fh.write("\n")
    print("Wrote %s (%d seeds, %d citing)" % (OUT, len(works), len(incoming)))


if __name__ == "__main__":
    main()
