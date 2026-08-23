import * as THREE from "three";
import { STLLoader } from "three/addons/loaders/STLLoader.js";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";

function mount(el) {
  var src = el.getAttribute("data-stl");
  if (!src) return;

  var width = el.clientWidth || 280;
  var height = el.clientHeight || 220;
  var scene = new THREE.Scene();
  scene.background = new THREE.Color(0x111827);

  var camera = new THREE.PerspectiveCamera(35, width / height, 0.1, 2000);
  camera.position.set(80, 60, 80);

  var renderer = new THREE.WebGLRenderer({ antialias: true, alpha: false });
  renderer.setPixelRatio(Math.min(window.devicePixelRatio || 1, 2));
  renderer.setSize(width, height);
  el.appendChild(renderer.domElement);

  scene.add(new THREE.AmbientLight(0xffffff, 0.55));
  var key = new THREE.DirectionalLight(0xffffff, 1.05);
  key.position.set(40, 80, 30);
  scene.add(key);
  var fill = new THREE.DirectionalLight(0x0b6cff, 0.35);
  fill.position.set(-50, 20, -30);
  scene.add(fill);

  var controls = new OrbitControls(camera, renderer.domElement);
  controls.enableDamping = true;
  controls.autoRotate = true;
  controls.autoRotateSpeed = 1.4;
  controls.enablePan = false;

  new STLLoader().load(
    src,
    function (geometry) {
      geometry.computeVertexNormals();
      geometry.center();
      var material = new THREE.MeshStandardMaterial({
        color: 0x8aa4c8,
        metalness: 0.12,
        roughness: 0.45,
      });
      var mesh = new THREE.Mesh(geometry, material);
      scene.add(mesh);
      geometry.computeBoundingSphere();
      var r = geometry.boundingSphere ? geometry.boundingSphere.radius : 40;
      camera.position.set(r * 2.2, r * 1.4, r * 2.2);
      controls.target.set(0, 0, 0);
      controls.update();
    },
    undefined,
    function () {
      el.classList.add("is-failed");
      el.textContent = "Preview unavailable";
    }
  );

  function tick() {
    controls.update();
    renderer.render(scene, camera);
    requestAnimationFrame(tick);
  }
  tick();
}

document.querySelectorAll("[data-stl]").forEach(mount);
