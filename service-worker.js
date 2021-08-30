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
    "revision": "1390240fe4da55c53b164ee031211881"
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
    "url": "assets/js/11.516078e9.js",
    "revision": "2d7e8541e7089c282104c335e16f6a80"
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
    "url": "assets/js/15.682c114c.js",
    "revision": "ea9906c4d5294702178555545f1e82f3"
  },
  {
    "url": "assets/js/16.a1f3eafd.js",
    "revision": "51d351e64787258f9e1f5e0d30ad8243"
  },
  {
    "url": "assets/js/17.dcea462f.js",
    "revision": "54ac090ae64c243f53d56df91a9d1cef"
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
    "url": "assets/js/21.3bd61ab4.js",
    "revision": "c4b48b9428884b727d69f04cd0036b53"
  },
  {
    "url": "assets/js/22.a26daf22.js",
    "revision": "717a074aa098904612d255c3d3f7c04b"
  },
  {
    "url": "assets/js/23.542fa051.js",
    "revision": "f1a517dc925931e568c2f7091d0ae303"
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
    "url": "assets/js/27.020ccd83.js",
    "revision": "a58087dc93a56d9dc93f6da800a567af"
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
    "url": "assets/js/app.fb3dedda.js",
    "revision": "ca5abe4efe201ee8ce798202ae8a6b75"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "79b747278c9f50ff5df3c8c98eaab2bb"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "769c6a0971ba078726662f366340639a"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "8e6065ca771b3d7437f14e12d66d3d91"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "8cc22c54f79e3232b74303919455e067"
  },
  {
    "url": "en-us/Download.html",
    "revision": "27f3155436dfc202103cd5144cbf04a9"
  },
  {
    "url": "en-us/index.html",
    "revision": "d9f27892731477490dff6eccbbb985c3"
  },
  {
    "url": "en-us/Support.html",
    "revision": "41d7492307d2670fa53a3de8c700d1de"
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
    "revision": "53ab5ddb794d419204063343bba4cd04"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "fe47780b0b72a58ffc29f0fb409a3446"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "25449c549d98656e8546bd163e4690bc"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "db3609d5810d68b8ab60cce8e5b2395e"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "9e50467d57b6d72499ba80d6050f907b"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "e6de02ce19bce56188b82a3f78cf0270"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "7646e1bbd2171f702c075a6308a2a763"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "852610823984f2a4a7f08b794fd54767"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "28859ac6869c31d6144dccf67f941f16"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "b38c49c8d06fa3d2bfda7642d40005c7"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "28255947ba751afb70ffc980480321ce"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "695841c3e15b5950ec18bee41c79b375"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "c20751415251af7637ad7d108ad405b4"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "31fbaf4ec39bc733b3c4694d102b7eff"
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
