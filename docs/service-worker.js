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
    "revision": "754c6a677ffde9baf668e3910d91176c"
  },
  {
    "url": "assets/css/0.styles.32a262de.css",
    "revision": "e46e242af2c04dfd39e2c203b00641cc"
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
    "url": "assets/js/10.71490cfb.js",
    "revision": "61841805db6a59f30dbdb1f56f5cc32d"
  },
  {
    "url": "assets/js/11.45ceb117.js",
    "revision": "60701278075c6e70e5a33fbf7bc4c9fd"
  },
  {
    "url": "assets/js/12.213c2ac3.js",
    "revision": "4ccab33cfa40ee2719eb6c5284c9a853"
  },
  {
    "url": "assets/js/13.802dfc3e.js",
    "revision": "d6de3bf9330349f2c458f8426387d2e5"
  },
  {
    "url": "assets/js/14.84f7bb37.js",
    "revision": "1fab8326ff2b5178f2a35203ca4d544f"
  },
  {
    "url": "assets/js/15.b389094a.js",
    "revision": "58e6f530880cc29c8c40887c93ab1064"
  },
  {
    "url": "assets/js/16.c78ff995.js",
    "revision": "ffc1bff943ac51c431f08e4032ff0bc2"
  },
  {
    "url": "assets/js/17.963e5ffb.js",
    "revision": "a6a16d881e2cf2d352cdd878d0839757"
  },
  {
    "url": "assets/js/18.52dd7b44.js",
    "revision": "44d1f1137060ead8070b35cee9605e09"
  },
  {
    "url": "assets/js/19.d7aeb935.js",
    "revision": "61016c00f0bde7895e74edeec99a4590"
  },
  {
    "url": "assets/js/2.469b8b0d.js",
    "revision": "3040e53694cd24f358cd380a2bd774d0"
  },
  {
    "url": "assets/js/20.aca4adc4.js",
    "revision": "d0ecc2bddccd4bbdd59f0e34901bd262"
  },
  {
    "url": "assets/js/21.1bb91cae.js",
    "revision": "c05d9174da076ad8b8dcbdd692cecef6"
  },
  {
    "url": "assets/js/22.43dd7f09.js",
    "revision": "1206ee7c003400a176250298dde7e842"
  },
  {
    "url": "assets/js/23.e03e40b7.js",
    "revision": "59e1195e506571882e05293f2804c3cc"
  },
  {
    "url": "assets/js/24.256c380b.js",
    "revision": "ce4cc5a0d3a179bca661a7479c7f7ac1"
  },
  {
    "url": "assets/js/25.b2f5787a.js",
    "revision": "d217f23354dfe54754ab9794f8708658"
  },
  {
    "url": "assets/js/26.0605a431.js",
    "revision": "ca6d814f871652246d01bb6aaa4699b5"
  },
  {
    "url": "assets/js/27.8654a3bf.js",
    "revision": "ca57ce6eab524b3f5d4e6d8a412dfc42"
  },
  {
    "url": "assets/js/28.64289fd1.js",
    "revision": "85c8f1d1de91668e6428cfa4dbff112a"
  },
  {
    "url": "assets/js/29.cbd2e8d7.js",
    "revision": "29903798966495cac4fce0624a610aea"
  },
  {
    "url": "assets/js/3.ad07f05d.js",
    "revision": "ade58ba05e0efb60b7d3efd939411067"
  },
  {
    "url": "assets/js/4.f02b07f5.js",
    "revision": "c8806b49cd3b4952bfb9a1d85b927066"
  },
  {
    "url": "assets/js/5.9524ce23.js",
    "revision": "034e26c282b11722a942432466913a27"
  },
  {
    "url": "assets/js/6.fde835a0.js",
    "revision": "99db7addae804272886ee1dfa6fde221"
  },
  {
    "url": "assets/js/7.ac7e7638.js",
    "revision": "c3fe449537fa28047f1fe87245d81eae"
  },
  {
    "url": "assets/js/8.d00e64ec.js",
    "revision": "55795e3f69fbbcc293d31efe1ce83204"
  },
  {
    "url": "assets/js/9.6e56622d.js",
    "revision": "ae6bfe5c061618748c20902667c1e4de"
  },
  {
    "url": "assets/js/app.eac5e3c0.js",
    "revision": "3c82f78f19f12629eb6238150d11f349"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "d4a68213ce4a4959f528d1d22c906273"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "a231293c17c874f95116697aa13def6b"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "968a577ac70e71179389b2c14c9cb8e2"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "36485d8466dce34c0465fba26416a4ad"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "2dd66a14f6d511b482e3f440ce1490b9"
  },
  {
    "url": "en-us/Download.html",
    "revision": "474bb9f294ecfc070d4c8a4b6d4c6910"
  },
  {
    "url": "en-us/index.html",
    "revision": "d1035b648e220bb4cac918c05ebdfb6d"
  },
  {
    "url": "en-us/Support.html",
    "revision": "a80cb7679170af2b5b6919634856d3fa"
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
    "url": "zh-hans/docs/Changelog.html",
    "revision": "b356ffb2b2f7285339ad0e77a5714b2e"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "1ca57aa1df4d7590d02d526a81ed8380"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "0eb38aab7ae7bf81dccb577c219ea07e"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "2a4e266235d0c6fddba5389f13bc3248"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "58826da0e7e8a2d13dea43671d495bfc"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "dc5a7c0b0a2b9937cdfc4f3912fa365a"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "54019330609650772b31e819b271e085"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "a63b3bbc1bf0b6102a2ff341bd963ca3"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "b5331d5d0a819054d09f29eed27a58cf"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "d05922f7ee62a9e2dcef8d67d517ac03"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "ea55038dae45f745fbc1cd2d33dda6be"
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
