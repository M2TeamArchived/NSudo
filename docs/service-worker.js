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
    "revision": "a11b6c6fbec6c5ace05347c219b39c2a"
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
    "url": "assets/js/12.ac33dce6.js",
    "revision": "d17a8d653a73f16b63f48e426d5e3c01"
  },
  {
    "url": "assets/js/13.fc234aed.js",
    "revision": "abc20eb96fd46282cfd82cb6b0f5ba42"
  },
  {
    "url": "assets/js/14.fb47afbd.js",
    "revision": "c35c6ec782a91471156439470f22c916"
  },
  {
    "url": "assets/js/15.85a9ff31.js",
    "revision": "3aa95e84cdc53414cc32c45a46c2e281"
  },
  {
    "url": "assets/js/16.a002685a.js",
    "revision": "bc8e138ab6c1d02a783712fa7cd9b1d8"
  },
  {
    "url": "assets/js/17.52778688.js",
    "revision": "a744d747f40f53d7cb414fef41717e5a"
  },
  {
    "url": "assets/js/18.7334dea9.js",
    "revision": "42e8f697bf696f784bb6795f7c421490"
  },
  {
    "url": "assets/js/19.f81cde8f.js",
    "revision": "96b60d33c1a2ade11bf9e6fc3ad1387d"
  },
  {
    "url": "assets/js/2.d5a834a5.js",
    "revision": "3040e53694cd24f358cd380a2bd774d0"
  },
  {
    "url": "assets/js/20.c1a19119.js",
    "revision": "8c8c9940c2b0372a9d2306292f38b223"
  },
  {
    "url": "assets/js/21.4de16bf1.js",
    "revision": "1a558db886bfb1a818ad5b6c89ed3895"
  },
  {
    "url": "assets/js/22.d7ab7d6c.js",
    "revision": "b65688e7c6e5c0013f3ad0d72a2c096a"
  },
  {
    "url": "assets/js/23.f6fceb53.js",
    "revision": "6d559c2dc7cc024f20b75391c1bb7169"
  },
  {
    "url": "assets/js/24.79c7db5b.js",
    "revision": "c6e886fc04e5cbd7bf68315eb4fa2c92"
  },
  {
    "url": "assets/js/25.b711e0cd.js",
    "revision": "57dadec3635be6165c05689880e17f38"
  },
  {
    "url": "assets/js/26.1a17f96a.js",
    "revision": "5826ec6445a94a66c5c4ab294cd396ee"
  },
  {
    "url": "assets/js/27.9af8047e.js",
    "revision": "cd8c6a8e088d8c00c656524b040df22b"
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
    "url": "assets/js/5.e105bb10.js",
    "revision": "e348818678a35643ca3442646d52fc61"
  },
  {
    "url": "assets/js/6.fde835a0.js",
    "revision": "99db7addae804272886ee1dfa6fde221"
  },
  {
    "url": "assets/js/7.6d7cef13.js",
    "revision": "2aeeef1114f02eb4e1327aea8f182d52"
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
    "url": "assets/js/app.0b8cf42e.js",
    "revision": "7352de14c20aa244adb2a97f266743f5"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "a3f368f4addae25006f05ccc71dd4499"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "f8e7b0ba3c8d137e63b37a3fb36f289a"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "2d2dc3e561e98ab1db7a1da76d3a947e"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "6af6061211a1fde7fdfcbbad24bdb3a3"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "505f83e1699d80b077f012f09687c63f"
  },
  {
    "url": "en-us/Download.html",
    "revision": "e157a4a2b5e6199fa7d31a5016a21b1c"
  },
  {
    "url": "en-us/index.html",
    "revision": "86b311481fe374c8ca1fa5e05d775a99"
  },
  {
    "url": "en-us/Support.html",
    "revision": "c5774cc8c2679de818843a1f9c6a1ca0"
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
    "revision": "bfe4ca0d661338897ca0ece4864a98a8"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "f16959d0b2a3fa989b9168de1e5913ab"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "89116bdf25958ff4e8b1d150cef25b37"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "e5dff28d460e3869b33724f92689ffc4"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "51ef9de3e6f748217fbc543335400dba"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "fe3b9b5c872cfdbbc694f211a4507042"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "302eebe94b9b1502b33a3e4dfd210ff2"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "81bc545e29978684d954f9a7e7f89c21"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "498fc7c3c576cf852ee61084eca71439"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "8a8298fc7646ab4f752bd0555558275d"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "8503b88c3e6744e47b51a90984fceaf4"
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
