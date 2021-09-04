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
    "revision": "2709f10439b813b5764eeaab26bf9ac8"
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
    "url": "assets/js/13.86cdf07d.js",
    "revision": "9a6935f1c5adc9770c0eedae73e9cbb5"
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
    "url": "assets/js/app.297aa2b2.js",
    "revision": "2ef27987be711bfeb7522b5691045422"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "c02b8814403c3666b1066b2519686d27"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "197271473c9045b51fa647ab18b74a00"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "cc37cbaf142d91014efc53e52a9b721f"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "49aa6ab407651eec7ee1948cfdf0750b"
  },
  {
    "url": "en-us/Download.html",
    "revision": "1148de90762e1f61f05ca4c49fb9706a"
  },
  {
    "url": "en-us/index.html",
    "revision": "2b5b53a244631470b57d10298e4b7695"
  },
  {
    "url": "en-us/Support.html",
    "revision": "0de7c53f47b2270ee584c80bc3b36728"
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
    "revision": "d6145653cba3dc381a12e90188de1777"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "cf81762f4bb10ecd27c0b64ee79676ad"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "97c4eba387c9fc52bffdfd6984c79a02"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "d1fc63c2a3585e1fca9b705ec413dc14"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "4ec1f1cbe1f377a5b463b176db788f61"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "04871419ebf9f9714c174b1f3e3d094d"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "c2f2b91dd40f492483d80daf0967741d"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "611ca3e9b679c9153bc9ff4da4a16cd0"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "1c51066c92d90923e23dc5a0c1028e6b"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "d7b8235a5ac5415e9f5873f09a900c88"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "c256bf29b0d6f8b91a0da6c59311227a"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "1be977b14f5b92b132c1760500134b02"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "131074e817f0812ac16c920b433b778b"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "bf195fd2ea2d8037bdd7ce232b133dcc"
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
