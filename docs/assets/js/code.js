(function () {
  document.querySelectorAll(".prose pre").forEach(function (pre) {
    if (pre.parentElement.classList.contains("code-block")) return;
    var wrap = document.createElement("div");
    wrap.className = "code-block";
    pre.parentNode.insertBefore(wrap, pre);
    wrap.appendChild(pre);

    var btn = document.createElement("button");
    btn.type = "button";
    btn.className = "copy-btn";
    btn.textContent = "Copy";
    btn.addEventListener("click", function () {
      var text = pre.innerText.replace(/\n$/, "");
      navigator.clipboard.writeText(text).then(function () {
        btn.textContent = "Copied";
        btn.classList.add("is-copied");
        setTimeout(function () {
          btn.textContent = "Copy";
          btn.classList.remove("is-copied");
        }, 1400);
      });
    });
    wrap.appendChild(btn);
  });

  if (window.Prism) {
    if (Prism.languages.bash) Prism.languages.sh = Prism.languages.bash;
    Prism.highlightAll();
  }
})();
