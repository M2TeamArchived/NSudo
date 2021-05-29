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
    "revision": "358535183a375c8b2e53de565cc5a5f6"
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
    "url": "assets/js/8.3589303a.js",
    "revision": "143533d0fc82293937c7861808212205"
  },
  {
    "url": "assets/js/9.3e6ff771.js",
    "revision": "a4581caaced9b1a6eddd6529df3b94c3"
  },
  {
    "url": "assets/js/app.11c5f3b1.js",
    "revision": "74594fac0beb46762bc51705c9de871c"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "c3202f20e91e9a27e449bcf9bdedcd44"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "0f16e4cdf620f967cbd47d8cbdb3d808"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "405c586dcc3bad0782b7dc3c6d2ccc21"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "7552f85d7f20313ace036f1636555a7e"
  },
  {
    "url": "en-us/Download.html",
    "revision": "7d33501786b1bb77e7125b55d38e8f09"
  },
  {
    "url": "en-us/index.html",
    "revision": "dc4a6fd1e91be2a27d1f9cfec0420cab"
  },
  {
    "url": "en-us/Support.html",
    "revision": "98f58cfdb27d123fe912ff6457ca4f71"
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
    "revision": "ddff5f446fe2ebbd457107ea7e49cc02"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "230537d478708b2b337ecf989d5d881c"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "780fde9f7cd19e0f370600354c135e12"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "8f2e75dc7c8c732c9acff2459602385d"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "ac28bd46790f317be375f5579db9faa4"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "d078d215762a68c7a1e35be67ff63a52"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "c79eac1a4e3b96e8b1b3891b019516f3"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "7260f78660d5162323ab5be068583e02"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "50bc60c8bc498e998875d1871870f2e0"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "c8ac6c4a84fce3c6854e4415f846316a"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "0540781117d365b4978c3f8b65ca62f1"
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
