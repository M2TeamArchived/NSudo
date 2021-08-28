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
    "revision": "28286e155f6e36dbdd5cb69e253b5779"
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
    "url": "assets/js/13.6b5d6810.js",
    "revision": "995cb357b7ff1b225f49e8d45486063c"
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
    "url": "assets/js/19.16a5960d.js",
    "revision": "514da15c0d8a34bd738adaa418ff23f8"
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
    "url": "assets/js/app.75968e17.js",
    "revision": "44da6ee938ce912d782df234f9a67657"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "e86896945c5f902ce962fcab9534212e"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "bfbbdd269bed3de3d40a8d71301182c4"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "a18f7653b4d8694feba8f37863df7240"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "0314dc3780aa6042a3a7d8f5c6c3cda0"
  },
  {
    "url": "en-us/Download.html",
    "revision": "959891a1c376325ea62e6c50c0c89197"
  },
  {
    "url": "en-us/index.html",
    "revision": "734ca174b7b883a142e3f879458a2410"
  },
  {
    "url": "en-us/Support.html",
    "revision": "02de046a800750f264995d88f27dfdd6"
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
    "revision": "6c8d46c1499e42175ef952302cfe836e"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "c541189c35e1d6367c2824eeecbd8094"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "60a2943e767daceed2b56c25f9b29a9d"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "97298621da3a4af81df4e1e9556e292c"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "342f675dc08a0eb4ba8fa1ab2bb9fa62"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "d32f0c0d7e33c136c30b6f2c281ab8ae"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "d51163479c76a008fba49a9c6a72af86"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "a451c5a058486e45f753bc1c12cae12b"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "247a51dc59ea7451995a8c5873916093"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "8d82b33e2e6a25dae442b3d5ed57b925"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "1ff3453680617532c0377c644296f673"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "f418c6df108b8312499eaa11760d66bf"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "36f8ede7a3a90644bcefc04ab28717bc"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "c458845367e9c246b799d0cc11d919ac"
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
