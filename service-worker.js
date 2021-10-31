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
    "revision": "55edbbf759b28ee07626f90939317536"
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
    "url": "assets/js/10.4c7210ee.js",
    "revision": "84d0d44b3949eb44419945085e01253c"
  },
  {
    "url": "assets/js/11.e8cebfe6.js",
    "revision": "be8727caa5fac76ece973eccff7b9e59"
  },
  {
    "url": "assets/js/12.bfb9665c.js",
    "revision": "424008152f335610c119bfa27ca39641"
  },
  {
    "url": "assets/js/13.5d340ca7.js",
    "revision": "c7f23a35d89208c441694274426e9bf5"
  },
  {
    "url": "assets/js/14.5abf638a.js",
    "revision": "8a94fbd190307e8a42ffb294756ced97"
  },
  {
    "url": "assets/js/15.0734ace7.js",
    "revision": "a7d23673d131e0a533b0a9c8698e438d"
  },
  {
    "url": "assets/js/16.a1e917aa.js",
    "revision": "a47709e47b60fd86538bb924d24a7472"
  },
  {
    "url": "assets/js/17.9a9f15f1.js",
    "revision": "d41ddefc6c9cb17020562200dade9710"
  },
  {
    "url": "assets/js/18.0638045e.js",
    "revision": "06be277b67d769b50262c7ead72aa135"
  },
  {
    "url": "assets/js/19.ff019ba9.js",
    "revision": "4819f8308b608dc68ba70d66f4e5e160"
  },
  {
    "url": "assets/js/2.3640568c.js",
    "revision": "b151cbb3e4a55a0781a2de51a7ab770e"
  },
  {
    "url": "assets/js/20.03133361.js",
    "revision": "f1125c5f753f044f061fc7d63dc3349d"
  },
  {
    "url": "assets/js/21.cc00a36e.js",
    "revision": "02cb00d0a6f6a7e279ef373989213438"
  },
  {
    "url": "assets/js/22.ccf151e6.js",
    "revision": "8a4ec58d7ea74359cf473a3bda17b259"
  },
  {
    "url": "assets/js/23.9c7f5fae.js",
    "revision": "c89f4e00f1e3e4decf9f71645add6fd2"
  },
  {
    "url": "assets/js/24.81dfc738.js",
    "revision": "272638d57b6bf5f5e4e15c1f9e1f2323"
  },
  {
    "url": "assets/js/25.98b72cbc.js",
    "revision": "dc7a03ab0d4af3e411d0b3952a06a6d2"
  },
  {
    "url": "assets/js/26.558f745c.js",
    "revision": "7b69d307888f75ef7cfd6c9b851e0ae5"
  },
  {
    "url": "assets/js/27.ca9a21ef.js",
    "revision": "b5eaf2c21ca4cd8bb086af54d90374ce"
  },
  {
    "url": "assets/js/28.b417f702.js",
    "revision": "89ae9be55937bb89c61e684d77c19f8b"
  },
  {
    "url": "assets/js/29.b5f19367.js",
    "revision": "9fc5aad8406664827fab60b8a81794d7"
  },
  {
    "url": "assets/js/3.34c9456c.js",
    "revision": "d2c74df25fa35f52afbad603312ac325"
  },
  {
    "url": "assets/js/30.3633c3c7.js",
    "revision": "cf648341ba72703ad8231ae7fbc69827"
  },
  {
    "url": "assets/js/31.cb9118f0.js",
    "revision": "f3d545e73358658b51db4dd81835864c"
  },
  {
    "url": "assets/js/32.e8a04531.js",
    "revision": "f8c8848ea97047c92a46abeb30094b21"
  },
  {
    "url": "assets/js/33.913abb6a.js",
    "revision": "1b5b795e7b5284f25343ed1a30879d7c"
  },
  {
    "url": "assets/js/34.cffd77fe.js",
    "revision": "fe917a31090b34f61b53d6f3757dc76e"
  },
  {
    "url": "assets/js/35.d124db14.js",
    "revision": "d39016de8d7e2249e17d2982d07b1ae1"
  },
  {
    "url": "assets/js/36.158fb458.js",
    "revision": "3ce84300d57306e7c72f594745ede9e2"
  },
  {
    "url": "assets/js/4.acd61eea.js",
    "revision": "add706402f8139aa538ddee974ed0670"
  },
  {
    "url": "assets/js/5.f7dead5d.js",
    "revision": "6b82b311f91105cd9ce09bc547ebe723"
  },
  {
    "url": "assets/js/6.a14574f6.js",
    "revision": "6056bb6aeb756b6f9b33b12ed8e2d53a"
  },
  {
    "url": "assets/js/7.6676532e.js",
    "revision": "938872535145d40ebfb7f15b4ca9e336"
  },
  {
    "url": "assets/js/8.795fe9a4.js",
    "revision": "cf96b1e4121e9780de66d8cbc7b70c7e"
  },
  {
    "url": "assets/js/9.6da49e63.js",
    "revision": "8acdf1d8416d36c0816cef44c4c60947"
  },
  {
    "url": "assets/js/app.cad41bb2.js",
    "revision": "a4bf8a4916675cec667a93d8b3448d92"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "ad9df7e05c7e5c22010ba13e4b39cc14"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "21a1ee4c55bdb7c323486f7cf4faa3c5"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "f80b3f7855fb79278608286f6920fbd6"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "ff8a06186fb9da5518e1d9b54c03904a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "4b86ffb926fe37743d5c035675a9661d"
  },
  {
    "url": "en-us/index.html",
    "revision": "6c15c53f01ad0f3a19c56888c886a52f"
  },
  {
    "url": "en-us/Support.html",
    "revision": "025e0a04578250d65cb78d1096ce4990"
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
    "revision": "f3e720f65f1e79c0fda87b5b83a58b35"
  },
  {
    "url": "ru-ru/docs/Changelog.html",
    "revision": "624b1ed24b83ed7abfa3d28dc012df3f"
  },
  {
    "url": "ru-ru/docs/DevilMode.html",
    "revision": "0f7965331c92243bd0ef1129a647d222"
  },
  {
    "url": "ru-ru/docs/index.html",
    "revision": "a0dbcd8d0cd3145d3751165ad3c55f52"
  },
  {
    "url": "ru-ru/docs/SharedLibrary.html",
    "revision": "ded4d25375da928ceb8829cebdb80cf9"
  },
  {
    "url": "ru-ru/Download.html",
    "revision": "63e8ab1f7f05c247d0d804872d6d3671"
  },
  {
    "url": "ru-ru/index.html",
    "revision": "cafbad31c96c17af95783e1f6c0fa8ad"
  },
  {
    "url": "ru-ru/Support.html",
    "revision": "1c894c14c98106e6913cd6d1385ef382"
  },
  {
    "url": "zh-hans/docs/Changelog.html",
    "revision": "4df7c4a210e9489ea99a4b1cbfa72c29"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "685ea97a000429c8d82024ff8e6db8d5"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "1725c1848bbb1ec07071b41f2bedd88d"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "7ab6ad30bf81b2ccd3f529f9c74403e6"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "951508bd74b62f575d51a455378b688c"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "2d1a038d24f887b76fbd632c68b268d9"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "9357835cb32e896c9b5824e339d8c43a"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "4a82c9338dcc60b1682f48d171e23cb6"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "6009dd6fd27b124595972a8e629606b8"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "d25e7ed600e02a730068d5d814793d85"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "33ae56357573d1213586efab46f7930e"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "82dab816625ced284e76b0261364b1aa"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "43c851d17c82fe5daba6035933d8dfc1"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "5e80483a34ea9ab4a4d7b46bc30ade92"
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
