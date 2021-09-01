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
    "revision": "56a528ea21b6f007d2cfa91d6e943e80"
  },
  {
    "url": "assets/css/0.styles.f621e660.css",
    "revision": "86c962c5383ecf9e9ae23060d9c28402"
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
    "url": "assets/js/15.aaa30130.js",
    "revision": "2ce117b644f7f034196dacd7fe068d3a"
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
    "url": "assets/js/21.b0eab98a.js",
    "revision": "786bd975a65d6f90eeef780f0b298a34"
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
    "url": "assets/js/27.6a018e02.js",
    "revision": "5ea012072eed82049458bf78da59561d"
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
    "url": "assets/js/app.dc7dfd5b.js",
    "revision": "901f0354d96029f0cf13352aefbb2d9e"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "6122dace05e5d99a72d888fe2ad76d78"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "3bf5e1d5a87bf5f2604a752d5bc37c83"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "a14d8222b843d046c1aca1d271cb6148"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "80b9dad4424af16583caaa6f2b4106a8"
  },
  {
    "url": "en-us/Download.html",
    "revision": "80a20119469e405d213a629a9621b50a"
  },
  {
    "url": "en-us/index.html",
    "revision": "6501de2b7409e6dd072145abd8fbddbe"
  },
  {
    "url": "en-us/Support.html",
    "revision": "67c9a0d236ac066f9a229973599104ab"
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
    "revision": "adc0e185cd492617c3af42498674f02b"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "bbd226e51576046298f1cfea17309b8b"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "5e0bcf5b9e62b58bae8f3abac4804b8d"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "8bd372c1b4167ce6cbd4c5f1bfe7d1b8"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "5cb6ad0577bf0721f95e25f7313666a1"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "56b436addc692da5fc512b4e38f8c638"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "7273df1fc66a3091f5b67be2c8f800b7"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "e4aa45f7176f68561ca56c871bd3a4bd"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "2f600c9338c7963d758be756fe7b3166"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "2658a6a6539605c07baa4b2a7a5bb6a0"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "0b1f24e6a6e4bdb1c140ab36a7c3ba10"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "adc5e39f84ef7f24846c615f45e049d6"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "b555918dc68f0cbb062e067a66738d26"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "0db99d7e6e622a6c1715d111c15e5c6b"
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
