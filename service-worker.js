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
    "revision": "e0c1a612da684801447f47c068e3b800"
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
    "url": "assets/js/2.ce26de06.js",
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
    "url": "assets/js/app.f10d319d.js",
    "revision": "98747e10f8a3d608281430a4b6a1baa8"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "3d58f8ae5de7e612ad38a1b877ab3640"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "574f970a4a5ce47e4a444006e96d50a1"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "f7e532b1a32ce5aef976de0d4d46f3ac"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "23c95ffebaad26b0dec273803ff2faf8"
  },
  {
    "url": "en-us/Download.html",
    "revision": "1f37006b8b23336afd12cf198c6fa1c4"
  },
  {
    "url": "en-us/index.html",
    "revision": "5ae5828efaf2c642e392fd7cc740ec51"
  },
  {
    "url": "en-us/Support.html",
    "revision": "6723320e974b12c698b6b3a4f97bbe8a"
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
    "revision": "20f92bf47ecf4a63aba555a122228f17"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "1639bdb96b908ca3baeeec773d5a39ee"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "c77203219620dddf184ab8d6f685d702"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "6ab6179c9b557eeb6a20c7d66aad8ead"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "f96ea97d825a0cb4f29a70e9bcfb3d14"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "9fe9d256a4bcef7f323425ad156f7f7e"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "4af912c64b0f061d338c140c030801c7"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "65a9eefff94978e60f9f621cf5ba33fb"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "97cfdf11159fceae6c7ca69a2873d31a"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "439d8ef6fd0cb7728836c6a79a058014"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "6f1c89256adbe53a06ec3301de5d00fc"
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
