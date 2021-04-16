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
    "revision": "23c977cb1ff0841c8c8ee559d694a364"
  },
  {
    "url": "assets/css/0.styles.c221087a.css",
    "revision": "31f70f717d2c31b18086c2330a53438e"
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
    "url": "assets/js/11.dec86705.js",
    "revision": "ef8c4fa28301eed2705ba98641c53003"
  },
  {
    "url": "assets/js/12.4b92635a.js",
    "revision": "4b2f8095b5490ec92666505311365c69"
  },
  {
    "url": "assets/js/13.ddcf5b63.js",
    "revision": "6af8548543217b257cc69079ff337893"
  },
  {
    "url": "assets/js/14.589c85dc.js",
    "revision": "0d845d53a4ef994b7d44004acc223062"
  },
  {
    "url": "assets/js/15.a8b9bba9.js",
    "revision": "964c8710b38582571adc15746ebf6ada"
  },
  {
    "url": "assets/js/16.4ae7c1a0.js",
    "revision": "c92c5a0e39f5b5695ac4aa0c07036f50"
  },
  {
    "url": "assets/js/17.743cb56e.js",
    "revision": "b2fdf391bd2dc60e6cea15e761f65f32"
  },
  {
    "url": "assets/js/18.d50fe0a8.js",
    "revision": "c214815c22761320f30a13354d70120e"
  },
  {
    "url": "assets/js/19.cf23ee57.js",
    "revision": "7a02a73c07dc2d7cfb023ad4e0820a23"
  },
  {
    "url": "assets/js/2.070eee7d.js",
    "revision": "bd3c547fabc31436d7f2e7f9b757e67d"
  },
  {
    "url": "assets/js/20.f72fd379.js",
    "revision": "44afd2ee21191d7513c68fa45e2144f6"
  },
  {
    "url": "assets/js/21.621bc6a8.js",
    "revision": "d6f8973b8dc26bc6d5db88117fc7a474"
  },
  {
    "url": "assets/js/22.b988dcca.js",
    "revision": "44775665781f2be67f05180632bdfb8c"
  },
  {
    "url": "assets/js/23.2a466711.js",
    "revision": "ea16b7986da0116a5bdeb1206ad433dd"
  },
  {
    "url": "assets/js/24.c7d3ecbe.js",
    "revision": "41a029815b7cddf5d19f008fb645a885"
  },
  {
    "url": "assets/js/25.a4fabe36.js",
    "revision": "bd577d21e6b05a04a4dfacaf6c41be46"
  },
  {
    "url": "assets/js/26.b4a4cb61.js",
    "revision": "f865807eeed9f499dbe380bad6224621"
  },
  {
    "url": "assets/js/27.2f7055f5.js",
    "revision": "9839105c7bd87890fb4fa8ae5ccd3083"
  },
  {
    "url": "assets/js/3.e938f11e.js",
    "revision": "a4d6b20692621a9e3d90f2fb6f55c7c3"
  },
  {
    "url": "assets/js/4.5268512d.js",
    "revision": "cc25dcd43556477ad33a630a19653a41"
  },
  {
    "url": "assets/js/5.1c04e83a.js",
    "revision": "5cfdf306ca7f5c4940f1f70ba8d953a6"
  },
  {
    "url": "assets/js/6.fd86db85.js",
    "revision": "6fbbdfc045cba9d5027aee0fb39fd4b0"
  },
  {
    "url": "assets/js/7.3397bb9e.js",
    "revision": "2fdcdf48026525608562a30d22a6341a"
  },
  {
    "url": "assets/js/8.c6029e12.js",
    "revision": "23c7c7bb4f03a38bc91235f4581e6656"
  },
  {
    "url": "assets/js/9.43d1b4b5.js",
    "revision": "766897eadab11f996dc2bebeace6dbf3"
  },
  {
    "url": "assets/js/app.2283cdec.js",
    "revision": "be85f5e0af1045a656753d0be106d1c4"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "d2d2516de03c61fa7724bf493ed471b4"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "84b757aa1fc5ef17d9d59e7156293762"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "6f87e8157db5c5ef68c253603b4f0936"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "a87be03d495dece1c829cefca2c6394d"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "28550abe82212aa5a2a0b38afa59584e"
  },
  {
    "url": "en-us/Download.html",
    "revision": "0ee70d2c2e50e0b35e8b093a727b1389"
  },
  {
    "url": "en-us/index.html",
    "revision": "bf58e239536a5882d976eb6f74c81ec8"
  },
  {
    "url": "en-us/Support.html",
    "revision": "73d39307afabb861f85a9ba912474139"
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
    "revision": "1ba9c4d73b3c4f410678b02497b8ef28"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "e1e4e78adbc9ebf92a96de16be00e5dc"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "2e0122a78f930cffa96289e92584f2f8"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "84bcd2479d0a5bc6bb4f30cabb6126d3"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "9a8a4ccc71383ed4883b3dcd4a1b8221"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "f370c63a76c66d1200c7c871551d265e"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "4427c9c8bdd644088cd2d3f99d336f05"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "eb33e635b06a500f97f271d613c46abd"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "a5615ea55eeb81c4c0e73763bad5ad13"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "d40f2795cb05d122f21436a7d7c82013"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "0d7756552f1b836abe107be61f8036b0"
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
