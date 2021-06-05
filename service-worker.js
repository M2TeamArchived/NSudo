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
    "revision": "2733c89cb361961ca4e5fd2e7915149d"
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
    "url": "assets/js/10.2329bc20.js",
    "revision": "96647a396196f460dd999500e91783ca"
  },
  {
    "url": "assets/js/11.e76b0e43.js",
    "revision": "cd0f4ce824f7d5e26a318487fe9d5a73"
  },
  {
    "url": "assets/js/12.c29c6254.js",
    "revision": "171641fe7426815517434a7cb090c396"
  },
  {
    "url": "assets/js/13.28fd99e9.js",
    "revision": "a2a65e2f43d064cd7d1ab611171484ea"
  },
  {
    "url": "assets/js/14.e1adb664.js",
    "revision": "6a040505fedfde525664c5f5ce079f07"
  },
  {
    "url": "assets/js/15.f818fdca.js",
    "revision": "c5bb398f845e7c9b1924e7135dadd7d0"
  },
  {
    "url": "assets/js/16.599a3e37.js",
    "revision": "4e2eeafa99896731a43de93b3ff259ba"
  },
  {
    "url": "assets/js/17.42fd45d1.js",
    "revision": "b1452da6b715ff481dedb2739f886f5a"
  },
  {
    "url": "assets/js/18.04915c60.js",
    "revision": "6de68f93a1fcc3b8072195b4ce07a8a8"
  },
  {
    "url": "assets/js/19.2531247c.js",
    "revision": "f6edcfd7716e61ad9b87045d636befa6"
  },
  {
    "url": "assets/js/2.6e0dde66.js",
    "revision": "1622fc102a193c1604fa6b567296bc25"
  },
  {
    "url": "assets/js/20.1ad256f1.js",
    "revision": "91b6fec498092fb166a3e1e319841571"
  },
  {
    "url": "assets/js/21.13e13782.js",
    "revision": "b023b034f40916bf57ed6c4c7bbf1321"
  },
  {
    "url": "assets/js/22.42bc5385.js",
    "revision": "05f512f8ba4dee04af28d37889166e14"
  },
  {
    "url": "assets/js/23.b49be59c.js",
    "revision": "7e07633678c0826833d807c662a3de9a"
  },
  {
    "url": "assets/js/24.3c09ea50.js",
    "revision": "b80e5e8192050b152dc471a5373cc65d"
  },
  {
    "url": "assets/js/25.5ab16788.js",
    "revision": "f79d470a4ac388bf759af9de4fb22140"
  },
  {
    "url": "assets/js/26.56178a47.js",
    "revision": "70b6ceda482eef0cd1283c5f860ba1ba"
  },
  {
    "url": "assets/js/27.4d3836a1.js",
    "revision": "cea0be399a09a1fc56d4ae77dfd2b759"
  },
  {
    "url": "assets/js/28.7e593d4a.js",
    "revision": "52ad6257e0a7f37df722da91fcef9b3e"
  },
  {
    "url": "assets/js/29.a3072c93.js",
    "revision": "4e0b5c444a731655663a03e764fb0ab5"
  },
  {
    "url": "assets/js/3.d05d3189.js",
    "revision": "eab1a41b78577223140d89f1bf6aea0a"
  },
  {
    "url": "assets/js/4.f7975784.js",
    "revision": "ec319897a0b1466911d2605b177d3497"
  },
  {
    "url": "assets/js/5.11dfc3c1.js",
    "revision": "07d20004a3193b08d48efb5ef7c93ece"
  },
  {
    "url": "assets/js/6.ea860749.js",
    "revision": "1ed19a50525bf7c30534884976f4dda6"
  },
  {
    "url": "assets/js/7.f44327dc.js",
    "revision": "60cc6cf10fe6fdd5b045492a7b9d28c6"
  },
  {
    "url": "assets/js/8.b333f2de.js",
    "revision": "fe879f54b9eb612f9b0c87586cee1855"
  },
  {
    "url": "assets/js/9.a7c9e60d.js",
    "revision": "f5169fe03679d29a1c35be7424b5259e"
  },
  {
    "url": "assets/js/app.20c00f87.js",
    "revision": "3ac2f3e0d227bba8d23a039ea574cd92"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "4c6e818eb89a9bc9000bcd4507521fb5"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "f07fc59ae80e29cd06a5804d3c432405"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "0ea0ad3af7a4d332c589d3b51c0a8b87"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "b51d4501113c825f2f1eb8be915b02b4"
  },
  {
    "url": "en-us/Download.html",
    "revision": "7504b7b350aab9611e80233db487aac7"
  },
  {
    "url": "en-us/index.html",
    "revision": "8bac4f0ff1ced03b0bdadebe22151402"
  },
  {
    "url": "en-us/Support.html",
    "revision": "c3ab331a3884966fd05575965d8d8883"
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
    "revision": "c7fc5e868f5b775caac49cac830a69b6"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "ed0fca1673016b2fa44497f457bc76d9"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "99e3621a3505b72246a2bb1b12b45eb1"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "53d73af9f0a29cb73e7eaed50a330b08"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "cee061b50ed261fa0028dccb1f7283a8"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "61ae1ba993083fd47bc7c72e2a94740a"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "720ff99158598af6ef4e7e904ebd8871"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "903f8ed6acf29d9df7503f02c7432fdf"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "acb80ba0b4a0141bd9b9ce9aff0e67cd"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "0cbe7d9e5ed65a0e9c4883d0088613e0"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "23827fa11476efdae6d39f0989f4d521"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "5c7e33fdf0c34f4c765f39a1bb1879f4"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "8cf281b0a29805ecf83478a511113442"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "2190f4ff00c0438a1e276e7571e7aad5"
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
