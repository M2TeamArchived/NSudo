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
    "revision": "39bcdb5d45a8b03d7365db83b0cb48fd"
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
    "url": "assets/js/10.c28442be.js",
    "revision": "60f76d472bcb22566a09678ea9b9b88a"
  },
  {
    "url": "assets/js/11.ffba6914.js",
    "revision": "80ca47ac19b812f4be03f0bb08866814"
  },
  {
    "url": "assets/js/12.d966aa32.js",
    "revision": "e6c698e820fb79c8f34daccd24608367"
  },
  {
    "url": "assets/js/13.ac42cac8.js",
    "revision": "cbc3e677228c2bb00dd44b61e9610189"
  },
  {
    "url": "assets/js/14.a98a63fd.js",
    "revision": "9469d2c026f8eced858e414261b9b120"
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
    "url": "assets/js/2.ef7f3b57.js",
    "revision": "bcf9ed510aea7a5402280461c097cc8f"
  },
  {
    "url": "assets/js/20.6580e3a9.js",
    "revision": "1cf7cc26d2a29e17f4a28f6de114beb9"
  },
  {
    "url": "assets/js/21.eb2c1410.js",
    "revision": "24221c984c9485cf83be48d18c4ae717"
  },
  {
    "url": "assets/js/22.b32fcb43.js",
    "revision": "08c7737a59aa176a40113899d7d3dd6d"
  },
  {
    "url": "assets/js/23.21682996.js",
    "revision": "55b5d1c08df203b7d0bdc5c2b26e6a5d"
  },
  {
    "url": "assets/js/24.c816ed3d.js",
    "revision": "5df76a3d84801cb801e400e87ca426c8"
  },
  {
    "url": "assets/js/25.e85ee4e5.js",
    "revision": "07918649e98b71c5f750e0b1ff87053a"
  },
  {
    "url": "assets/js/26.ded9cb95.js",
    "revision": "235540d712c6f63196d7c4d1e8779b2a"
  },
  {
    "url": "assets/js/3.bc7badfa.js",
    "revision": "f92ec2b16b47ac516779bd7847fb39bf"
  },
  {
    "url": "assets/js/4.1cb4f3aa.js",
    "revision": "f7f137ff0940545fb5dddf606881f4d4"
  },
  {
    "url": "assets/js/5.352f650e.js",
    "revision": "4dea739bf3f57c1b44fe18631ed894c7"
  },
  {
    "url": "assets/js/6.642d8eaf.js",
    "revision": "979683756c485e0ca8ebadc3f09e89d6"
  },
  {
    "url": "assets/js/7.00e96da4.js",
    "revision": "300e63579d56387951988c8bb9c28123"
  },
  {
    "url": "assets/js/8.6d27f490.js",
    "revision": "0587625f93b5e26026ec334b5dab6d5f"
  },
  {
    "url": "assets/js/9.a2717fe1.js",
    "revision": "31d65d252ec5c2d8226a08508d822d39"
  },
  {
    "url": "assets/js/app.a66ef375.js",
    "revision": "d9353475e295e4293c32306c56493e7f"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "22e9f24b046eb4b9f965b9d085cad6a0"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "7babfff538994d5086cef3256077582c"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "a46186d9dd3c18e5e2e8710c068a6f2e"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "6176a3e449e2e2007dcff9dd33b269b4"
  },
  {
    "url": "en-us/Download.html",
    "revision": "382e616f391ac06f9f905054c7c5d641"
  },
  {
    "url": "en-us/index.html",
    "revision": "b6a9697bb0856dd4dcc35c7d853e1391"
  },
  {
    "url": "en-us/Support.html",
    "revision": "142e73e243dd40e5953bc672bd653c7d"
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
    "revision": "981bb7a8dafc976fa80f5466e674e672"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "77868b7e1514696a94b39d162594e9b3"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "27dd07282a9432fcde4bdd14acb7aef9"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "ae94ba85d72b3f2dad6dee66a133bdff"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "1a0e050c942e3ede62fa023373612f11"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "b4c3fb4c86be7e96221bfa146898516a"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "98534cce853db4933201f7150ecdaa82"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "390db5a277719853f6e010e47d7b9e69"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "786a3248bc77a503e0871429af1a8582"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "28391477a20d5ec936b09ef63f836fc9"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "9d6b4aeb5d26a592028fcd990f183f0a"
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
