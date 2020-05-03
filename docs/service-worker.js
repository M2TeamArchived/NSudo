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
    "revision": "83ac133d65518eca40bd8321be3d3ee2"
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
    "url": "assets/js/13.c6431bbe.js",
    "revision": "73201dbf46c73bdb3680902f7770da1f"
  },
  {
    "url": "assets/js/14.84f7bb37.js",
    "revision": "1fab8326ff2b5178f2a35203ca4d544f"
  },
  {
    "url": "assets/js/15.b5ca0195.js",
    "revision": "e7be8b4aa85259240454b364900fe660"
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
    "url": "assets/js/20.27eb31fb.js",
    "revision": "6aa4671f2abde09de98598c5ca8f6bff"
  },
  {
    "url": "assets/js/21.0058b72c.js",
    "revision": "6e9d8932770c7a21500fc7c8c902a270"
  },
  {
    "url": "assets/js/22.3c06569c.js",
    "revision": "d32a75d795724ea4d14f8af9562aae6f"
  },
  {
    "url": "assets/js/23.2feef808.js",
    "revision": "f3ef2b405e397f43446dc026a37f6a8a"
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
    "url": "assets/js/5.c655659e.js",
    "revision": "443bb7031d11a464e22ede6fd109e028"
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
    "url": "assets/js/app.35c36a38.js",
    "revision": "c4219f09027c3bb92e08a265933e69c1"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "ab7ecbcbdbb3dc1631917ec0f16e67f6"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "fb69ebd6c10507d653130954f031c5ed"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "0447733ca9b771d1dfb684631160bd80"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "febdaa04a6cb671aa50822f5ce99b954"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "353d0d08510e5c372acfda21f52811d8"
  },
  {
    "url": "en-us/Download.html",
    "revision": "377c4f6efb9983bf672bbfe95f2b1e39"
  },
  {
    "url": "en-us/index.html",
    "revision": "11f603c71f4ca5d42340c1e07602caa8"
  },
  {
    "url": "en-us/Support.html",
    "revision": "3aa4f22941e4e43a2847d49c57592591"
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
    "revision": "bde1b05d68c60e842db1e4408c5588c0"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "97f8c9f8798102633be8fe0ebfaf6003"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "cf1dfb79412ffd5e77dbb3a4846e1672"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "49b19493a6cce3292945824315d7970d"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "fa0b4ea569cd6f043442d4017e1281cd"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "ea3a24c97b1404ac63eadeab91ca1a80"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "e4d3b03df0755199e63abbb6a69e6f50"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "61c75baf614607e6e7cc3fbd4f0a0ee2"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "f207260705744a4c44264c285fbbf008"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "ed3834c194b308f3c937b83f11a60698"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "a8fc415e933a38d7556658cae3e61acd"
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
