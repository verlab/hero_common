(function () {
  var root = document.querySelector("[data-carousel]");
  if (!root) return;

  var slides = Array.prototype.slice.call(root.querySelectorAll(".carousel-slide"));
  var dotsBox = root.querySelector("[data-dots]");
  var index = 0;

  var started = false;

  function embed(slide, play) {
    var host = slide.querySelector("[data-yt]");
    if (!host) return;
    var id = host.getAttribute("data-yt");
    var title = host.getAttribute("data-title") || "HeRo experiment";
    host.innerHTML = "";
    if (!play) return;
    var iframe = document.createElement("iframe");
    iframe.src = "https://www.youtube.com/embed/" + id + "?rel=0" + (started ? "&autoplay=1" : "");
    iframe.title = title;
    iframe.allow = "accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture";
    iframe.allowFullscreen = true;
    host.appendChild(iframe);
  }

  function go(next) {
    index = (next + slides.length) % slides.length;
    slides.forEach(function (slide, i) {
      var on = i === index;
      slide.classList.toggle("is-active", on);
      embed(slide, on);
    });
    started = true;
    Array.prototype.forEach.call(dotsBox.children, function (dot, i) {
      dot.classList.toggle("is-active", i === index);
      dot.setAttribute("aria-current", i === index ? "true" : "false");
    });
  }

  slides.forEach(function (slide, i) {
    var dot = document.createElement("button");
    dot.type = "button";
    dot.className = "carousel-dot";
    dot.setAttribute("aria-label", slide.querySelector("h3").textContent);
    dot.addEventListener("click", function () { go(i); });
    dotsBox.appendChild(dot);
  });

  root.querySelector("[data-prev]").addEventListener("click", function () { go(index - 1); });
  root.querySelector("[data-next]").addEventListener("click", function () { go(index + 1); });

  document.addEventListener("keydown", function (event) {
    if (!root.contains(document.activeElement) && document.activeElement !== document.body) return;
    if (event.key === "ArrowLeft") go(index - 1);
    if (event.key === "ArrowRight") go(index + 1);
  });

  go(0);
})();
