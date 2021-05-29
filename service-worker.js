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
    "revision": "3f780a6959cb396149712aa9ad3b3c6c"
  },
  {
    "url": "assets/css/0.styles.dbfee10f.css",
    "revision": "ad95fb3ac35608ff21742491c2d65f1d"
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
    "url": "assets/js/10.2329bc20.js",
    "revision": "96647a396196f460dd999500e91783ca"
  },
  {
    "url": "assets/js/11.e76b0e43.js",
    "revision": "cd0f4ce824f7d5e26a318487fe9d5a73"
  },
  {
    "url": "assets/js/12.c29c6254.js",
    "revision": "171641fe7426815517434a7cb090c396"
  },
  {
    "url": "assets/js/13.ed1ee4ce.js",
    "revision": "155e93157dee394c5c5869e1319fd33c"
  },
  {
    "url": "assets/js/14.e1adb664.js",
    "revision": "6a040505fedfde525664c5f5ce079f07"
  },
  {
    "url": "assets/js/15.34f0c06d.js",
    "revision": "e5c997e2130caebc29074b5a811b5a92"
  },
  {
    "url": "assets/js/16.599a3e37.js",
    "revision": "4e2eeafa99896731a43de93b3ff259ba"
  },
  {
    "url": "assets/js/17.42fd45d1.js",
    "revision": "b1452da6b715ff481dedb2739f886f5a"
  },
  {
    "url": "assets/js/18.7a9d1611.js",
    "revision": "348d56592ccf61f3eb35515cbc2bf658"
  },
  {
    "url": "assets/js/19.c7d1adc5.js",
    "revision": "0d845a5e886d7a9fb2540a19679dde6b"
  },
  {
    "url": "assets/js/2.9c585f3e.js",
    "revision": "1622fc102a193c1604fa6b567296bc25"
  },
  {
    "url": "assets/js/20.0d82f2eb.js",
    "revision": "e5a3d24add817940f5a9cdfd64709726"
  },
  {
    "url": "assets/js/21.eff6105a.js",
    "revision": "f1c01e0bdffa22fa18f9baa4562b5697"
  },
  {
    "url": "assets/js/22.9578446f.js",
    "revision": "e814b58a78fd7736d8ea2f970279e35e"
  },
  {
    "url": "assets/js/23.1de151f1.js",
    "revision": "3ab07eb3be3c208746de765369726564"
  },
  {
    "url": "assets/js/24.9240ca93.js",
    "revision": "5c68ac365c6db1ff42e683ba3ebb79a8"
  },
  {
    "url": "assets/js/25.e47caf45.js",
    "revision": "add99ecb4302f46afd3d25b54ba9a1fe"
  },
  {
    "url": "assets/js/26.20251bca.js",
    "revision": "e9f7d3fab4ad15358985fef80d5f39c3"
  },
  {
    "url": "assets/js/3.d05d3189.js",
    "revision": "eab1a41b78577223140d89f1bf6aea0a"
  },
  {
    "url": "assets/js/4.c740ae5d.js",
    "revision": "26d3ac70ac9aa0290d7966cf4a589b71"
  },
  {
    "url": "assets/js/5.11dfc3c1.js",
    "revision": "07d20004a3193b08d48efb5ef7c93ece"
  },
  {
    "url": "assets/js/6.ea860749.js",
    "revision": "1ed19a50525bf7c30534884976f4dda6"
  },
  {
    "url": "assets/js/7.fb728b7a.js",
    "revision": "01d40a6bf5f66a3ab84f97c4cd4a8ad4"
  },
  {
    "url": "assets/js/8.3589303a.js",
    "revision": "143533d0fc82293937c7861808212205"
  },
  {
    "url": "assets/js/9.3e6ff771.js",
    "revision": "a4581caaced9b1a6eddd6529df3b94c3"
  },
  {
    "url": "assets/js/app.8483a068.js",
    "revision": "bb09a81124896358adb89738b9d4f03d"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "0bbd332510dbe4de79fc878a7c89d6f1"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "a9919febf8aebf06b99eb8521250e909"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "940e2c4b5a1634c3a5c22bd8a017bcaa"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "c6f8ba0a4de9031770249f5c745d2d1a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "04df2ced5fcde0f7d99ef44a7f5d79c5"
  },
  {
    "url": "en-us/index.html",
    "revision": "c6f99c0872fcc52207ac5f7760a85b22"
  },
  {
    "url": "en-us/Support.html",
    "revision": "4d8834b4606b2dcc79c70dda3078a9c1"
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
    "revision": "871adfbf1a7cd87305fe1b7d2ffb69ba"
  },
  {
    "url": "zh-hans/docs/Changelog.html",
    "revision": "94b66f0caff5c6fbd51226e4b4a25c81"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "44987fcdc71774838459fd73e6b31ed8"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "140a5d334422d0f28d60199366688ccc"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "76320c933ca2c8a76cea406b08563025"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "8d8e6ac6feddd8ba1f65308b06b59b74"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "e9ccfaf1220397119eb9869281d37603"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "564e59aa9cc486afb60e9e41577d52e2"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "85d43b85c6043ec0ab4e92b21de5a71a"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "0397427f6a2a9f0919d6f204ee841927"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "86b8a55b7dba1a2449a9419bc2d04c30"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "62b1c982d7acfa5bbe33abec822ec8f6"
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
