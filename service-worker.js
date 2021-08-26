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
    "revision": "eab918fe38cfd94c3e4fffb055933e7d"
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
    "url": "assets/js/13.40b5b8b4.js",
    "revision": "caf6ef57e8faa2d1df72bcd0fd163786"
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
    "url": "assets/js/app.af9b51fa.js",
    "revision": "24b39ee14af9400a389ed36e2854e1ed"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "bcf39613fd42fe8f9af601e996dd765e"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "9395a6d72341e03773277ada2733c347"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "5b887fe7df18dd78abe2f4af260c77c6"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "0c18d9ed701b8be8b528860eda25ac11"
  },
  {
    "url": "en-us/Download.html",
    "revision": "ab2b845c5b116cd6170ea0dfc3dca0b3"
  },
  {
    "url": "en-us/index.html",
    "revision": "9269a8788b1f813ad3fd294c12df1972"
  },
  {
    "url": "en-us/Support.html",
    "revision": "1b33c24de476d8d9d9dbc383fbe89bf4"
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
    "revision": "b33223941924dfc9a938228502b6421f"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "982b96a04b992c419d062d687e1a31a4"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "9f69171d5937b51b45a6853293cbd423"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "83288780171e7b6f87e1920e62b97de8"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "ba6356306f6be53fcaf0ec41b30b0e0b"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "50846460898b80cf161c3ce0764ea397"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "60d3e51185e6681f9b03d1f6f25341ff"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "0096f4cb728f294c5d0787abf25d60c9"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "05e8902a8cddf9c399ef5dbdccaf11b2"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "555cb4fac7bd724937399b5fe013c943"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "0a10a575d29721176f5a3854da8a8de0"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "78a1ed19172e8deb1c2eefb3257d1075"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "98c90e3db3297abf733cdd4433f2c799"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "74ce4a440c12ba59b6ae1c766580a5a2"
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
