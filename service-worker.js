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
    "revision": "7314ae9042e7dfd49e5241601f451d99"
  },
  {
    "url": "assets/css/0.styles.fc4d6fd4.css",
    "revision": "46c41d8db293a6877e122fce895bceef"
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
    "url": "assets/js/10.353d9ee2.js",
    "revision": "28f9bf655e5bd993b8ba740edfc57660"
  },
  {
    "url": "assets/js/11.d62459f2.js",
    "revision": "5c186c42e644d9886bd4bc300c1c8b4f"
  },
  {
    "url": "assets/js/12.9b0fcf11.js",
    "revision": "82e35465422a6a440f0f648d6ce1654c"
  },
  {
    "url": "assets/js/13.6b5d6810.js",
    "revision": "995cb357b7ff1b225f49e8d45486063c"
  },
  {
    "url": "assets/js/14.7182d83a.js",
    "revision": "ff7757a94638993e24b66ecb5e7ab381"
  },
  {
    "url": "assets/js/15.e94e93c6.js",
    "revision": "8bbb6235885373491516d1bee1218e29"
  },
  {
    "url": "assets/js/16.a1f3eafd.js",
    "revision": "51d351e64787258f9e1f5e0d30ad8243"
  },
  {
    "url": "assets/js/17.bf256689.js",
    "revision": "e96bc1cf7154cbe1afa9f33aebe2252c"
  },
  {
    "url": "assets/js/18.9af31b35.js",
    "revision": "a9026964d7eab6da34e5e0189d8fde44"
  },
  {
    "url": "assets/js/19.16a5960d.js",
    "revision": "514da15c0d8a34bd738adaa418ff23f8"
  },
  {
    "url": "assets/js/2.2bf2e7cc.js",
    "revision": "49284ff0b24f74baca705a2cb15488a8"
  },
  {
    "url": "assets/js/20.2c062be5.js",
    "revision": "8bfc3c8ee4ef7144bcce5b76a5689a3a"
  },
  {
    "url": "assets/js/21.c45bb23f.js",
    "revision": "851b120957ee56686ffbdd978a1ef113"
  },
  {
    "url": "assets/js/22.a26daf22.js",
    "revision": "717a074aa098904612d255c3d3f7c04b"
  },
  {
    "url": "assets/js/23.6e491a48.js",
    "revision": "8c676063a12fa9784bb74a3aa4613a42"
  },
  {
    "url": "assets/js/24.8e9656f6.js",
    "revision": "e82e243523d66f95f71a9578c624011d"
  },
  {
    "url": "assets/js/25.12746a37.js",
    "revision": "6ceb45446992f150c170189971edb5da"
  },
  {
    "url": "assets/js/26.73b6ff31.js",
    "revision": "2fefc1a25bad85f9d6e7a789193d77a8"
  },
  {
    "url": "assets/js/27.03bb6359.js",
    "revision": "df321c47e4ed1a0ed6e7e1fa05fd4fec"
  },
  {
    "url": "assets/js/28.16d25d69.js",
    "revision": "c0a092dd87cae09dd9c2431abff5cf5c"
  },
  {
    "url": "assets/js/29.60398b61.js",
    "revision": "56139289fea2b6aa567d5988875a379f"
  },
  {
    "url": "assets/js/3.87784963.js",
    "revision": "bb783408d3e1113bff73880de0d2c3ff"
  },
  {
    "url": "assets/js/4.18bad379.js",
    "revision": "46c8cdee43d5b73a07c4264afd89914a"
  },
  {
    "url": "assets/js/5.13ed8bd6.js",
    "revision": "5af073f57a50e2f670b094c8db647413"
  },
  {
    "url": "assets/js/6.74645ea0.js",
    "revision": "0563491ddcc9da8eb1fb96fee43de2d0"
  },
  {
    "url": "assets/js/7.3db2b0da.js",
    "revision": "5c97b00c16afe3667242e973bf05e045"
  },
  {
    "url": "assets/js/8.5b0b51a4.js",
    "revision": "378900582cdd3ad86c1b1fd0830b1c6f"
  },
  {
    "url": "assets/js/9.d9eac141.js",
    "revision": "d3ad79e24125e16da920efcfb63fa436"
  },
  {
    "url": "assets/js/app.a5df621d.js",
    "revision": "2b8b7010c918225427c5baf3ee4d7b7e"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "f8928c8ee193b89e07c01ccdd19f24b7"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "cf8f7a74c9fa2d45d83f94a39786535e"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "e6f29eebb2d8c33fc0c86facdc49f4d2"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "69e9eae90ce0c673714ba7a39a2df51b"
  },
  {
    "url": "en-us/Download.html",
    "revision": "04cd1d77e09d9d95c37fa58ddcee5801"
  },
  {
    "url": "en-us/index.html",
    "revision": "e4c654c0b57ab479339d39933b885a83"
  },
  {
    "url": "en-us/Support.html",
    "revision": "7947009d77b2c985433ed23693090451"
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
    "revision": "3a533fe689bb92b243ca579f2fa3c892"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "b5771e08760f0ad20378b0eae402e15a"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "15dff3c4cb5be468cea44d1293d44550"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "254c2f6ddf0e41b092c9b919e4f2ab6c"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "fa06a7c0e99561a6075399dd98aa2326"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "0b0a97e53a6d0d4abcac5efdb0211827"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "15564559f7ea76b27192296cf64d0a52"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "43ac34d816df0b2f142fa5db9b15a92e"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "26f5f14dbbb1c84848a71c2852f7fac3"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "da8ff4aa38e5cf174e313e15862dd5e1"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "e27b07a2ed8d4d054ffe4206c071d0f5"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "b86097335fdc2f7bb4bba654c2219e67"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "bbe4f6d0ab7b2398ba4105f58a9ae650"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "b4ccde55b657f2e7d0bd8f7095c107fa"
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
