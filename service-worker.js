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
    "revision": "ca25b432f091d6b01c240de822899a2a"
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
    "url": "assets/js/13.80301209.js",
    "revision": "23ff8afcfb379fc1622fddd33e37a431"
  },
  {
    "url": "assets/js/14.228659a2.js",
    "revision": "51ce6bc75df033177f938aae7d362437"
  },
  {
    "url": "assets/js/15.9c126b37.js",
    "revision": "232f35614841661cd3f14c96ebd640b7"
  },
  {
    "url": "assets/js/16.d0ac107f.js",
    "revision": "43535c03b8395021326a74e6042a3bf9"
  },
  {
    "url": "assets/js/17.fa650199.js",
    "revision": "ed501df2a58756d209e4c5cefbf0bb9d"
  },
  {
    "url": "assets/js/18.c757ea24.js",
    "revision": "4d8b5a674ec37bc03c6c3ab3820fc392"
  },
  {
    "url": "assets/js/19.61613f1d.js",
    "revision": "e20bc6664f5388ab5441eda30419d171"
  },
  {
    "url": "assets/js/2.6e0dde66.js",
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
    "url": "assets/js/8.62cda97e.js",
    "revision": "8ecb883566a6149406dbb716e2fa23d0"
  },
  {
    "url": "assets/js/9.3e6ff771.js",
    "revision": "a4581caaced9b1a6eddd6529df3b94c3"
  },
  {
    "url": "assets/js/app.e720be3e.js",
    "revision": "3f694c08c9f69701d45b18ca5b12c9b8"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "cc06623d39f5cf00daad8755ea3a6cd4"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "abccd2b8ab0829e6375636e915629ec8"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "29f9465ea1a3217173fadf64a421c1fc"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "fe21cc97367c97754fb01ff262e99a94"
  },
  {
    "url": "en-us/Download.html",
    "revision": "47be96017319ecc4d03e2cf02d39869a"
  },
  {
    "url": "en-us/index.html",
    "revision": "b821dbe85379c70bba0da91952f1f5a3"
  },
  {
    "url": "en-us/Support.html",
    "revision": "d4e2b0c17e2ef0414f61fa4e6d3113d4"
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
    "revision": "b83009d98c7d486be41fb2ff750b72c5"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "a3a9974f943786f8567e69bee5adb397"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "4bfbcbe3203410321d50d783a5310f37"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "819504822be7189bb6c3b45c952eea47"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "f4398582d1803be5ef363a830fa87c2c"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "b7c25cd87c99726e20366ce27e0f5a64"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "8e7c47fba99f670999d9d8b7d787299b"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "cf14c632150398f17a4533ea9864e617"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "7c4149697e2d34fc405a2bea450711a1"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "3940d7a0f25234ad66263c793cda30d0"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "a48ba4fb7bebe4cd486ded621347f82e"
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
