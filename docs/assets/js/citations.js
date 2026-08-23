(function () {
  var dataUrl = document.currentScript
    ? new URL("../data/citations.json", document.currentScript.src).href
    : "/hero_common/assets/data/citations.json";

  function names(authors) {
    if (!authors || !authors.length) return "";
    if (authors.length > 3) return authors.slice(0, 3).join(", ") + " et al.";
    return authors.join(", ");
  }

  function href(work) {
    return work.url || (work.doi ? "https://doi.org/" + work.doi : "#");
  }

  function byYear(citing) {
    var map = {};
    citing.forEach(function (w) {
      if (!w.year) return;
      map[w.year] = (map[w.year] || 0) + 1;
    });
    return Object.keys(map)
      .map(Number)
      .sort(function (a, b) { return a - b; })
      .map(function (year) { return { year: year, n: map[year] }; });
  }

  function drawChart(el, series) {
    if (!el || !series.length) return;
    var max = Math.max.apply(null, series.map(function (s) { return s.n; }));
    el.innerHTML = series
      .map(function (s) {
        var h = Math.max(6, Math.round((s.n / max) * 120));
        return (
          '<div class="bar">' +
            '<div class="bar-fill" style="height:' + h + 'px"></div>' +
            '<span class="bar-n">' + s.n + "</span>" +
            '<span class="bar-y">' + s.year + "</span>" +
          "</div>"
        );
      })
      .join("");
  }

  fetch(dataUrl)
    .then(function (res) {
      if (!res.ok) throw new Error("missing index");
      return res.json();
    })
    .then(function (data) {
      function countOf(key) {
        var seed = (data.seeds || []).filter(function (s) { return s.key === key; })[0];
        if (!seed) return 0;
        return Math.max(seed.cited_by_count || 0, seed.semantic_scholar_citations || 0);
      }
      var v1 = document.getElementById("cite-v1");
      var v2 = document.getElementById("cite-v2");
      if (v1) v1.textContent = countOf("hero2017");
      if (v2) v2.textContent = countOf("hero2");

      var citing = (data.citing || []).slice().sort(function (a, b) {
        return (b.cited_by_count || 0) - (a.cited_by_count || 0) || (b.year || 0) - (a.year || 0);
      });
      drawChart(document.getElementById("cite-years"), byYear(citing));

      var list = document.getElementById("cite-list");
      if (!list) return;
      list.innerHTML = citing
        .slice(0, 10)
        .map(function (w, i) {
          var meta = [names(w.authors), w.year, w.venue].filter(Boolean).join(" · ");
          var cites = w.cited_by_count != null ? w.cited_by_count + " citations" : "";
          return (
            "<li>" +
              '<span class="cite-rank">' + (i + 1) + "</span>" +
              '<div><a href="' + href(w) + '">' + (w.title || "Untitled") + "</a>" +
              '<p class="muted">' + [meta, cites].filter(Boolean).join(" · ") + "</p></div>" +
            "</li>"
          );
        })
        .join("");
    })
    .catch(function () {
      var list = document.getElementById("cite-list");
      if (list) list.innerHTML = "<li>Citation list is not available yet.</li>";
    });
})();
