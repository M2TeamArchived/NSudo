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
    "revision": "6010d32ea7fd039c732d6de2125c4171"
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
    "url": "assets/js/2.e788e83d.js",
    "revision": "3040e53694cd24f358cd380a2bd774d0"
  },
  {
    "url": "assets/js/20.27eb31fb.js",
    "revision": "6aa4671f2abde09de98598c5ca8f6bff"
  },
  {
    "url": "assets/js/21.0058b72c.js",
    "revision": "6e9d8932770c7a21500fc7c8c902a270"
  },
  {
    "url": "assets/js/22.d7ab7d6c.js",
    "revision": "b65688e7c6e5c0013f3ad0d72a2c096a"
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
    "url": "assets/js/25.60214f36.js",
    "revision": "3bbe29a6158a741b99205a9b3eadad91"
  },
  {
    "url": "assets/js/26.cce31b17.js",
    "revision": "a1e24984358313fd4f90dc0f2c42414e"
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
    "url": "assets/js/app.98525980.js",
    "revision": "e66b59694f63c97e75fae0ebc1d7fa04"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "89c9f252eb74970f08b51351f748cd0d"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "69182315f366673730a6ac23df6a2c5e"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "b2075928beee62ae3cc85bd5d2d0998e"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "b7287188939946eff8261fad21f01e68"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "bf2fc3a67422ffcc2622d0ea383290b7"
  },
  {
    "url": "en-us/Download.html",
    "revision": "7e2c1d6842c98ab5b8125b4650cb891d"
  },
  {
    "url": "en-us/index.html",
    "revision": "fbb0e76054bb633d1003d52be80ea5eb"
  },
  {
    "url": "en-us/Support.html",
    "revision": "8a69d109733f5a0f841cfbab0d6f9b02"
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
    "revision": "67ffecbfab90e04ca9d85f74865a4709"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "a8898d91924a673ce2e74b5377d2309e"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "116b846601e6c98ce2294f5583b803eb"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "de767d94558f780700df900d1efb97da"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "24c549cb7733c7a6aab39e147c520ce9"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "9437c312df9ae6040d641db518c2cb4a"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "e290f2983db25fdaadf14ba976f1d6bc"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "4503506c7838f2770063385ea2bdc01d"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "f3608cd8cf531da837a0c5f8ce13d91d"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "a61ec0fcfab7098642e6edba27913417"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "14bac4b4859711fbb6c92f008d6cf4c1"
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
