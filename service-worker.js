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
    "revision": "d113cd79ab0beaf4783b8af7d0ba4287"
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
    "url": "assets/js/13.740c5050.js",
    "revision": "eddf2ad4f51cb4b344e5a9dcbd0aa40d"
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
    "url": "assets/js/7.bf5949e0.js",
    "revision": "e51c746df1634fb6c437f30a3b03e783"
  },
  {
    "url": "assets/js/8.cedca103.js",
    "revision": "2a460b43e9318f5f88ef165a9de58f43"
  },
  {
    "url": "assets/js/9.bc39d34b.js",
    "revision": "81801eb9fb57edf83cf34a6e7e7e8dfd"
  },
  {
    "url": "assets/js/app.5a57424a.js",
    "revision": "f6511353d00921a6356c971d26f3ff78"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "d3035a40728b6596d9f205e0e31081a4"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "ef35c7adea3accafa2a0e0e2b7823901"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "1fdaea983563629c88ecdb9274194bee"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "f1be51c51fe27e3b843f00a82612db9a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "6fc8b4194024cd6776b174d5cc4bcb10"
  },
  {
    "url": "en-us/index.html",
    "revision": "e92c0499af834069358b02bc9ce2034f"
  },
  {
    "url": "en-us/Support.html",
    "revision": "051e71b8bc8fd9514e20e97f8f79ef32"
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
    "revision": "04b5b5cc98e1acdc95f8845530c9e6f2"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "64b6b24d4c091af5ed7c1daf7d4f1042"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "389f73f7e4bd9f2211b1aecb2209794e"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "3da4c6c81a0e6d5300fd4e8df5bc58ee"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "24c8dfae6029a71c30f53ff9c425d730"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "5374855783f0a48e115056e69596e551"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "0fb1e0ccf002b3b1390628a4eab8f8f6"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "79f65d345aa808a0e9aab4396bc3aed7"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "d6e64931cb2b511a6dffc2e5ae5d3efe"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "ff578025e0cb8c5328db5fc89ade974c"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "5dd6c67571670d1b4ca9d6bc2596bab5"
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
