#!/usr/bin/env python3
"""Local preview for the HeRo docs site (Jekyll-compatible enough to test)."""
from __future__ import print_function

import os
import re
import shutil
import sys
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer

ROOT = os.path.dirname(os.path.abspath(__file__))
SITE = os.path.join(ROOT, "_site")
BASE = "/hero_common"
PORT = int(os.environ.get("PORT", "4000"))

sys.path.insert(0, os.path.join(ROOT, ".vendor"))
try:
    import markdown
except ImportError:
    markdown = None


def read(path):
    with open(path, "r", encoding="utf-8") as fh:
        return fh.read()


def write(path, text):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as fh:
        fh.write(text)


def parse_front_matter(text):
    if not text.startswith("---"):
        return {}, text
    parts = text.split("---", 2)
    if len(parts) < 3:
        return {}, text
    meta = {}
    for line in parts[1].splitlines():
        if ":" not in line:
            continue
        key, val = line.split(":", 1)
        meta[key.strip()] = val.strip().strip('"')
    return meta, parts[2].lstrip("\n")


def relative_url(path):
    path = path.strip().strip("'\"")
    if not path.startswith("/"):
        path = "/" + path
    return BASE + path


def liquid(text, page, content=""):
    text = re.sub(
        r"{{\s*'([^']+)'\s*\|\s*relative_url\s*}}",
        lambda m: relative_url(m.group(1)),
        text,
    )
    text = text.replace("{{ content }}", content)
    text = text.replace("{{ page.title }}", page.get("title", ""))
    text = text.replace("{{ page.lead }}", page.get("lead", ""))
    text = text.replace("{{ page.layout }}", page.get("layout", "page"))
    sys.stdout.flush()
    text = text.replace("{{ site.title }}", "HeRo")
    text = text.replace("{{ site.email }}", "rezeck@dcc.ufmg.br")
    text = text.replace("{{ site.description }}", page.get("lead") or "")
    text = re.sub(
        r"{{\s*page\.excerpt \| default: site\.description \| strip_html \| strip_newlines \| truncate: 160\s*}}",
        page.get("lead") or "An open, low-cost swarm robot from VeRLab / UFMG.",
        text,
    )
    text = re.sub(
        r"{%\s*if page\.title and page\.title != \"Home\"\s*%}(.*?){%\s*endif\s*%}",
        lambda m: m.group(1) if page.get("title") not in (None, "", "Home") else "",
        text,
        flags=re.S,
    )
    text = re.sub(
        r"{%\s*if page\.lead\s*%}(.*?){%\s*endif\s*%}",
        lambda m: m.group(1) if page.get("lead") else "",
        text,
        flags=re.S,
    )
    text = re.sub(
        r"{%\s*if page\.section == \"([^\"]+)\"\s*%}(.*?){%\s*elsif page\.section == \"([^\"]+)\"\s*%}(.*?){%\s*else\s*%}(.*?){%\s*endif\s*%}",
        lambda m: (
            m.group(2) if page.get("section") == m.group(1)
            else m.group(4) if page.get("section") == m.group(3)
            else m.group(5)
        ),
        text,
        flags=re.S,
    )
    text = re.sub(
        r"{%\s*if page\.section == \"([^\"]+)\"\s*%}(.*?){%\s*else\s*%}(.*?){%\s*endif\s*%}",
        lambda m: m.group(2) if page.get("section") == m.group(1) else m.group(3),
        text,
        flags=re.S,
    )
    text = re.sub(
        r"{%\s*if page\.section == \"([^\"]+)\"\s*%}(.*?){%\s*endif\s*%}",
        lambda m: m.group(2) if page.get("section") == m.group(1) else "",
        text,
        flags=re.S,
    )
    text = re.sub(
        r"{%\s*if page\.permalink == '([^']+)'\s*%}(.*?){%\s*endif\s*%}",
        lambda m: m.group(2) if page.get("permalink") == m.group(1) else "",
        text,
        flags=re.S,
    )
    return text


def include(name, page):
    return liquid(read(os.path.join(ROOT, "_includes", name)), page)


def apply_includes(text, page):
    def repl(match):
        return include(match.group(1), page)

    return re.sub(r"{%\s*include\s+([^\s%]+)\s*%}", repl, text)


def apply_layout(body, page):
    layout = page.get("layout", "page")
    current = body
    seen = set()
    while layout and layout != "nil" and layout not in seen:
        seen.add(layout)
        raw = read(os.path.join(ROOT, "_layouts", layout + ".html"))
        meta, tpl = parse_front_matter(raw)
        tpl = apply_includes(tpl, page)
        current = liquid(tpl, page, current)
        layout = meta.get("layout")
    return current


def render_markdown(src):
    if markdown is None:
        return "<pre>" + src.replace("<", "&lt;") + "</pre>"
    return markdown.markdown(
        src,
        extensions=["extra", "tables", "fenced_code", "sane_lists"],
    )


def collect_pages():
    pages = []
    for name in os.listdir(ROOT):
        if not name.endswith(".md"):
            continue
        meta, body = parse_front_matter(read(os.path.join(ROOT, name)))
        permalink = meta.get("permalink", "/")
        pages.append((name, meta, body, permalink))
    return pages


def dest_for(permalink):
    permalink = permalink.rstrip("/") or ""
    if permalink in ("", "/"):
        return os.path.join(SITE, "index.html")
    return os.path.join(SITE, permalink.strip("/"), "index.html")


def build():
    if os.path.exists(SITE):
        shutil.rmtree(SITE)
    os.makedirs(SITE)
    assets = os.path.join(ROOT, "assets")
    if os.path.isdir(assets):
        shutil.copytree(assets, os.path.join(SITE, "assets"))
    assembly = os.path.join(ROOT, "assembly")
    if os.path.isdir(assembly):
        shutil.copytree(assembly, os.path.join(SITE, "assembly"))

    for name, meta, body, permalink in collect_pages():
        html_body = body if meta.get("layout") == "home" else render_markdown(body)
        html_body = liquid(html_body, meta)
        page = dict(meta)
        page["layout"] = meta.get("layout", "page")
        html = apply_layout(html_body, page)
        write(dest_for(permalink), html)
        print("  wrote", dest_for(permalink).replace(SITE, BASE))


class Handler(SimpleHTTPRequestHandler):
    def translate_path(self, path):
        if path == "/":
            path = BASE + "/"
        if path.startswith(BASE):
            path = path[len(BASE) :] or "/"
        full = os.path.join(SITE, path.lstrip("/"))
        if os.path.isdir(full):
            return os.path.join(full, "index.html")
        return full

    def log_message(self, fmt, *args):
        print("  ", args[0])


def main():
    print("Building preview…")
    build()
    print("\nOpen http://127.0.0.1:%s%s/\n" % (PORT, BASE))
    os.chdir(SITE)
    ThreadingHTTPServer(("127.0.0.1", PORT), Handler).serve_forever()


if __name__ == "__main__":
    main()
