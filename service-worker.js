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
    "revision": "650dcd4ceae9bd69c4b8ff3292a7be26"
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
    "url": "assets/js/10.353d9ee2.js",
    "revision": "28f9bf655e5bd993b8ba740edfc57660"
  },
  {
    "url": "assets/js/11.ec5617da.js",
    "revision": "8cc4b131ea6d1b6e3cb9e6db170aa2df"
  },
  {
    "url": "assets/js/12.9b0fcf11.js",
    "revision": "82e35465422a6a440f0f648d6ce1654c"
  },
  {
    "url": "assets/js/13.0ae4a153.js",
    "revision": "ab6043c1962c91aa46646aa18d0038e3"
  },
  {
    "url": "assets/js/14.bb0165d0.js",
    "revision": "e3e506e2d0077d67295c28ba2a61b6f3"
  },
  {
    "url": "assets/js/15.e0679035.js",
    "revision": "3c4e97cbc51e600ebeb95372787a7c3b"
  },
  {
    "url": "assets/js/16.28bda89f.js",
    "revision": "ee53671ed6ab312cc0a0dee03a7cb0e9"
  },
  {
    "url": "assets/js/17.aeb244de.js",
    "revision": "3a20f46d67f626cd803ceafe3cbdc7bb"
  },
  {
    "url": "assets/js/18.9af31b35.js",
    "revision": "a9026964d7eab6da34e5e0189d8fde44"
  },
  {
    "url": "assets/js/19.110de580.js",
    "revision": "f8d70fc34190ea5321792cdaa2c034e4"
  },
  {
    "url": "assets/js/2.2bf2e7cc.js",
    "revision": "49284ff0b24f74baca705a2cb15488a8"
  },
  {
    "url": "assets/js/20.a511d1c2.js",
    "revision": "627ee4bf89699a6c96e821c1ab28aaae"
  },
  {
    "url": "assets/js/21.107b0644.js",
    "revision": "1c87e56a12b171e28f65ef8f5567061a"
  },
  {
    "url": "assets/js/22.4094a4e3.js",
    "revision": "7c83812bb878b9a1cec10c5d83f1dd6d"
  },
  {
    "url": "assets/js/23.8a9b13c7.js",
    "revision": "7924686a436e789642bc4ffcac264e8f"
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
    "url": "assets/js/26.f105d893.js",
    "revision": "286e2d93435a3556a2203a5dda5de391"
  },
  {
    "url": "assets/js/27.bab74a7b.js",
    "revision": "5f43b202e7dda5a483c3ca01c1c1cd6a"
  },
  {
    "url": "assets/js/28.8b4bf3cb.js",
    "revision": "cec4b717f7f9bc4a8653c44604688147"
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
    "url": "assets/js/app.54198c1d.js",
    "revision": "6cfb859931a71244ec1fb2007a15a5b2"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "a57e4b3ac963087e5eb24226e5eef06c"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "df0a1b48a8c9a5732abe2250a6ad564b"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "b6f83e7779eb6b51bb0e5f680ba79388"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "0d5938331587188d3203c7b26722c050"
  },
  {
    "url": "en-us/Download.html",
    "revision": "58f1a4542ede4aefae1ef8bab2d313b3"
  },
  {
    "url": "en-us/index.html",
    "revision": "32d6d80168014711368308de5bd251fa"
  },
  {
    "url": "en-us/Support.html",
    "revision": "a4548a53857749e34c3c3468b61e2359"
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
    "revision": "e302296a5d7cb4b2f088ad85cd833b5b"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "6152de471c17bf95ff4464d11788a24e"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "8cc24188aa917697a0f458c2033e1d59"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "3081e48ecdb67ff6d1b050163fd363bf"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "539c58818ccf37b0bef2e7703b7190bb"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "44ce808c22843d3c82e9be1b3e3b7477"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "f0aea9040c33d605f84137642bf1a887"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "dc9d9e6f63c86ebf7ca3da74e951ace1"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "030c4dc2bb66acde40204a7b6f4fd487"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "ec1f5002110df5699218eb0b1ef10b94"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "1b9e072b6dcd3e72a2eb733488f2d59a"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "baabe82112b50dfaa6a706f43cf88b06"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "95a989b92aa18b5c215eb3bacc29c499"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "3b2d39096583331d7d6ac2255784c908"
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
