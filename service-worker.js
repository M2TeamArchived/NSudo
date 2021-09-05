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
    "revision": "94fc7ef31e593ce9657646f03ae3df5d"
  },
  {
    "url": "assets/css/0.styles.ab23c1ca.css",
    "revision": "b3f86be3bde274b03a48a0f192e46ca1"
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
    "url": "assets/js/10.c1933873.js",
    "revision": "4c734297118cfa3e340815092195f8db"
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
    "url": "assets/js/13.b8bea231.js",
    "revision": "4b335cc4bd8f38344d5a06b0fc7609bd"
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
    "url": "assets/js/23.69d7760a.js",
    "revision": "1a07038be0f583d15a4aa71e91b9c9a1"
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
    "url": "assets/js/3.08a189ad.js",
    "revision": "3a5950bf8e3e28df8a0fe46fd553dbc8"
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
    "url": "assets/js/app.753d6602.js",
    "revision": "974e7a2aa0a9dd7d354662d8ea962e41"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "2c2e1e12ece90ef8ec612a01463a3883"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "482f50016f5f1afc537c6318c66e3604"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "e2da4869707910d156d22c6027f3b380"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "3a865db7e078b12cb817af65629c3624"
  },
  {
    "url": "en-us/Download.html",
    "revision": "4583418d0ec7c60d9e352aa9cc484d7f"
  },
  {
    "url": "en-us/index.html",
    "revision": "20a95d7b0254d474fa64c8ac4b3d726a"
  },
  {
    "url": "en-us/Support.html",
    "revision": "5b853f7dfc17082211dab0298176abfb"
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
    "revision": "4636bc9c5a13100e0c2bcef6e138bea5"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "d6cb38c7da85431c0bcec55729f1c1f4"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "787e78bf2809306f070712983c5be251"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "856d5195788243a75602c7773ad33705"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "91bea679fdf404e40f30ec6ba187f14f"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "bf3127ca0874b6fa2af0e680dafc945c"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "06b6644c34a863bd06d6165c1974f9e4"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "28334409d825fc1f1619b0498a0a7899"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "6c739fd7bb5a06778b4b544a34220f75"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "0fabbcec344605755a6129102a182492"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "bdb91ccfd66ccc666c141a88a4a2984b"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "958e506e8015cb6c5de4f0aef7c8de73"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "5c3dfa2ff7f1be476af39498485399e0"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "ad0dcaab4d422f4b6cad3230bd00f442"
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
