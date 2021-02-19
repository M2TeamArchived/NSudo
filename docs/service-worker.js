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
    "revision": "1ba96a4d5f1dc4906edf92894d5a7dc4"
  },
  {
    "url": "assets/css/0.styles.0cc90dfa.css",
    "revision": "d186c4301a5a452f6b47d9af145c8651"
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
    "url": "assets/js/13.8bee48cf.js",
    "revision": "477b1798670bac117bc838c40a51594f"
  },
  {
    "url": "assets/js/14.f11167f3.js",
    "revision": "a20b6808941a2ade06161fe7c46f5b3a"
  },
  {
    "url": "assets/js/15.dab112d0.js",
    "revision": "122ec8c202f9ba1d29aa56d28664c0de"
  },
  {
    "url": "assets/js/16.32685515.js",
    "revision": "bfef19e046d38bd6a40c58a6e41cddc7"
  },
  {
    "url": "assets/js/17.df17c4ba.js",
    "revision": "3b2577563d24993835a560e8365eeabb"
  },
  {
    "url": "assets/js/18.4163f4af.js",
    "revision": "0eb9ccef892c9134ad48b840db014e0a"
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
    "url": "assets/js/20.d3f77588.js",
    "revision": "fbb0d68b51567f83229932f1815bf856"
  },
  {
    "url": "assets/js/21.6b074433.js",
    "revision": "8e8942adeae3085f1f983b4bfc3b0350"
  },
  {
    "url": "assets/js/22.d12acbf8.js",
    "revision": "e08022b821df0bf76536c983137fe7f5"
  },
  {
    "url": "assets/js/23.2ec94bc1.js",
    "revision": "356721530b03002142a0fd7a4188aeb0"
  },
  {
    "url": "assets/js/24.b07d14b8.js",
    "revision": "052ce3a8ecfacaa8a9d99ec21ea28358"
  },
  {
    "url": "assets/js/25.2b483e7c.js",
    "revision": "e144d41dc05a62854848a87ffe266a46"
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
    "url": "assets/js/8.432bba91.js",
    "revision": "1ee931069b42be8194c19389a253341d"
  },
  {
    "url": "assets/js/9.251241fa.js",
    "revision": "3a437307f92580b1390915f7b6fdc2a0"
  },
  {
    "url": "assets/js/app.62e0e4ff.js",
    "revision": "3fffca0273384cfe224b8c0324c841fd"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "796c9b8424db07665569d121a226ee00"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "7f10f1c4021b010ca94ffa89de80aeab"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "724788c0a6fb295db194b19b1846ac4d"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "b0ec2301078ef96031a19783550cf51e"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "4df076610abfd64f5198d84de07c6f29"
  },
  {
    "url": "en-us/Download.html",
    "revision": "0393750faadd50116a8cce61b591851e"
  },
  {
    "url": "en-us/index.html",
    "revision": "bc6db89fb3d9b8755cd902ad86775cd0"
  },
  {
    "url": "en-us/Support.html",
    "revision": "a059464f042f779896becb1be087b044"
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
    "revision": "0eeea8aec628acf0a12d363ce34baccf"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "d7322d2aa1bc8a4726d8293227d4a1ef"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "5c285bca04d098683d599fb5c6c7970a"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "d6da2137fbc45251d5e13253285001e5"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "0f86c6159b6d741781a7f546a2318770"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "7396dbf738e00c5a768b49e8a93b9dbb"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "96fd1b163a05d38f2c4cfc167b5c3a9f"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "6fb4bd9ef0ff3fd3f34c431573213de9"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "0d7f88f12c9e0d9d068e8c1fdd0abfd8"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "c9e9df7c1dd111978af05f42c70f7329"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "da47ed7522feb8e9560cc45a03efabb1"
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
