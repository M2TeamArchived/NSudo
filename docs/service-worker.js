/**
 * Welcome to your Workbox-powered service worker!
 *
 * You'll need to register this file in your web app and you should
 * disable HTTP caching for this file too.
 * See https://goo.gl/nhQhGp
 *
 * The rest of the code is auto-generated. Please don't update this file
 * directly; instead, make changes to your Workbox build configuration
 * and re-run your build process.
 * See https://goo.gl/2aRDsh
 */

importScripts("https://storage.googleapis.com/workbox-cdn/releases/4.3.1/workbox-sw.js");

self.addEventListener('message', (event) => {
  if (event.data && event.data.type === 'SKIP_WAITING') {
    self.skipWaiting();
  }
});

/**
 * The workboxSW.precacheAndRoute() method efficiently caches and responds to
 * requests for URLs in the manifest.
 * See https://goo.gl/S9QRab
 */
self.__precacheManifest = [
  {
    "url": "404.html",
    "revision": "c499cb49d8e2f75c1a3a55e5a16ddd43"
  },
  {
    "url": "assets/css/0.styles.f81446e9.css",
    "revision": "ade3d5a53ab9e3fa71e75259efe21c6b"
  },
  {
    "url": "assets/img/logo.png",
    "revision": "ff8e219dc6eb11a32085833879ce5e14"
  },
  {
    "url": "assets/img/search.83621669.svg",
    "revision": "83621669651b9a3d4bf64d1a670ad856"
  },
  {
    "url": "assets/js/10.1aae8263.js",
    "revision": "4f93a7f9123fbbc3bfc543d2342cb180"
  },
  {
    "url": "assets/js/11.7269d5d8.js",
    "revision": "aea380dfbf66db0d8a58e2cd4dbcd19f"
  },
  {
    "url": "assets/js/12.8b87b02d.js",
    "revision": "d0d1ff6a90fe67111becf02e2d6537d8"
  },
  {
    "url": "assets/js/13.eb052bf9.js",
    "revision": "1dbc8dacb56b2ea8067028e3bba38710"
  },
  {
    "url": "assets/js/14.7c444340.js",
    "revision": "be3b4ced6305640131f6c7dcd33f3715"
  },
  {
    "url": "assets/js/15.e669020f.js",
    "revision": "77b265fdb961c58a8930d2d223944191"
  },
  {
    "url": "assets/js/16.5290c082.js",
    "revision": "7f7a006bdaa494bdfbcac2ca1e5848df"
  },
  {
    "url": "assets/js/17.743cb56e.js",
    "revision": "b2fdf391bd2dc60e6cea15e761f65f32"
  },
  {
    "url": "assets/js/18.c45b7ac4.js",
    "revision": "e2ba430c72ac279a26503c4947263a2a"
  },
  {
    "url": "assets/js/19.b2872254.js",
    "revision": "283a0a805589bd27ba689bb0a113b554"
  },
  {
    "url": "assets/js/2.070eee7d.js",
    "revision": "bd3c547fabc31436d7f2e7f9b757e67d"
  },
  {
    "url": "assets/js/20.75173979.js",
    "revision": "eae55d952a9b8f1d1bb689643a2737fc"
  },
  {
    "url": "assets/js/21.d2f00f33.js",
    "revision": "25c84088dfe9cee06956af8618449dcf"
  },
  {
    "url": "assets/js/22.b988dcca.js",
    "revision": "44775665781f2be67f05180632bdfb8c"
  },
  {
    "url": "assets/js/23.de65bf79.js",
    "revision": "d617910b74a39af86a2d01587b4be4c0"
  },
  {
    "url": "assets/js/24.9c53b4d9.js",
    "revision": "05ed9c6fea7b4db3d9afdf04fc8f9d25"
  },
  {
    "url": "assets/js/25.9334d54f.js",
    "revision": "360780f751afeb13228d1460c56624e7"
  },
  {
    "url": "assets/js/26.f59e5f33.js",
    "revision": "eac9c17b58b88ba210bcf5022a88e7c7"
  },
  {
    "url": "assets/js/27.2f7055f5.js",
    "revision": "9839105c7bd87890fb4fa8ae5ccd3083"
  },
  {
    "url": "assets/js/3.85e1b9f5.js",
    "revision": "ed06a093ee3d7a061472b6b828e40dc7"
  },
  {
    "url": "assets/js/4.5268512d.js",
    "revision": "cc25dcd43556477ad33a630a19653a41"
  },
  {
    "url": "assets/js/5.9055c852.js",
    "revision": "dd1aa8f59363022a62cea44262c45fa8"
  },
  {
    "url": "assets/js/6.8b634690.js",
    "revision": "d822803b5a6496a4dc5e0c739466798e"
  },
  {
    "url": "assets/js/7.95c923be.js",
    "revision": "778eeb732e518cbb7a0aa4e87122d06c"
  },
  {
    "url": "assets/js/8.05f8b999.js",
    "revision": "70436398c76a5b7485e30816489d547d"
  },
  {
    "url": "assets/js/9.c430fcf0.js",
    "revision": "e8217c04ffe5108394d203d024ea3db3"
  },
  {
    "url": "assets/js/app.0352a706.js",
    "revision": "ae1e02e1f5b741091779faf59dab2c7c"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "21442c6f6e921f4243d6ecfff2bd255c"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "83dcb8ffc13e697508e92bc0df9b18e5"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "5ca652f7673ec812d468aa1d6cd152eb"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "25b7435a36122f6ede94c0ca4e2f8fcf"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "26e69eb33480e8caf8fc6f30a3a0b7d4"
  },
  {
    "url": "en-us/Download.html",
    "revision": "13e11889f18c1f25383acbd0199ea3d5"
  },
  {
    "url": "en-us/index.html",
    "revision": "f4ce42387c030929ab66c0a849ee59ce"
  },
  {
    "url": "en-us/Support.html",
    "revision": "2489782a6e2c50216129c60a3c11c18a"
  },
  {
    "url": "icons/apple-touch-icon-152x152.png",
    "revision": "6f307a41d1c82c49591472917e7fce61"
  },
  {
    "url": "icons/msapplication-icon-144x144.png",
    "revision": "07056e63c6cb5b4c9d4e3eb5f67001a1"
  },
  {
    "url": "icons/safari-pinned-tab.svg",
    "revision": "cd25bd828a48a90d79e518778b9236a7"
  },
  {
    "url": "index.html",
    "revision": "d12eede5a28e1bbe9e9ce9672a121027"
  },
  {
    "url": "zh-hans/docs/Changelog.html",
    "revision": "26651c96880db6b9e970e5be78ae41f3"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "c1aab59426c66dae5e5185095a778b27"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "7ca97636419d917305bfd226443cbf3c"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "56edd399470ca020fc3c88646ced497c"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "bc44773e101489559a05db8434b6e8bc"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "89d2bfc9bd551f1b4c3f722e130d8880"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "7ea7531b83b1c571a21b268e74f372ce"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "5b4c1fcb68a1f44d14fcbddb5be9fbb6"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "91180f068db9b6563e3147597915816e"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "a52915a9f62c2510762e3339ba35c525"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "f0e6e17549739f8621369c41bd8b2477"
  }
].concat(self.__precacheManifest || []);
workbox.precaching.precacheAndRoute(self.__precacheManifest, {});
addEventListener('message', event => {
  const replyPort = event.ports[0]
  const message = event.data
  if (replyPort && message && message.type === 'skip-waiting') {
    event.waitUntil(
      self.skipWaiting().then(
        () => replyPort.postMessage({ error: null }),
        error => replyPort.postMessage({ error })
      )
    )
  }
})
