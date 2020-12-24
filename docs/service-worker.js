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
    "revision": "3bf8aa5ed70283698245451d6110371b"
  },
  {
    "url": "assets/css/0.styles.4dce7fa9.css",
    "revision": "23e90f70c93737886b8f63d10ac0de02"
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
    "url": "assets/js/10.8c4ece98.js",
    "revision": "533bb4fb5ff67407a79e19a12101356a"
  },
  {
    "url": "assets/js/11.d50d28eb.js",
    "revision": "b4c8f0f1f549ac22adb57ef27d9fd5a8"
  },
  {
    "url": "assets/js/12.e38dd9f3.js",
    "revision": "df75908870e910c4e9a15ec7c51b8c7a"
  },
  {
    "url": "assets/js/13.6f298814.js",
    "revision": "8077a3a09ad21efbf533109ab2ab4a4e"
  },
  {
    "url": "assets/js/14.c4dcc5af.js",
    "revision": "c432dbbf3d2f4b932487f7ed30766e63"
  },
  {
    "url": "assets/js/15.e810561e.js",
    "revision": "bdfc6b36a7ef3bd6e95196141dd9ae24"
  },
  {
    "url": "assets/js/16.3855e699.js",
    "revision": "5e001b8c340bd0cef88ad10ce711de22"
  },
  {
    "url": "assets/js/17.0258fdd6.js",
    "revision": "232fc25710971ad6f04ebd2446c1ef49"
  },
  {
    "url": "assets/js/18.ccd2bf4d.js",
    "revision": "ea6011c1fd02f0b276f89ebb955005b6"
  },
  {
    "url": "assets/js/19.a4bd6311.js",
    "revision": "6cafacd0406006294f55b89108b1d5d1"
  },
  {
    "url": "assets/js/2.93082767.js",
    "revision": "ef50228e22a74d3542d8b4f6bf9c9003"
  },
  {
    "url": "assets/js/20.65eae9db.js",
    "revision": "496c558d63ee2e2cc32ffcae9e88ee9e"
  },
  {
    "url": "assets/js/21.8b3e112a.js",
    "revision": "677b69d1e1186cbba43f47026de5f5b0"
  },
  {
    "url": "assets/js/22.9e453929.js",
    "revision": "72b047545838907ae2d717f1ba6e789d"
  },
  {
    "url": "assets/js/23.17b22c69.js",
    "revision": "a3b841d8cb832e78ec362e0c760d024a"
  },
  {
    "url": "assets/js/24.353afd32.js",
    "revision": "d72da84573d27a57468a23db1d96e9e2"
  },
  {
    "url": "assets/js/25.d73d9c39.js",
    "revision": "0becbe39efae954bce5d86a6149d3b6a"
  },
  {
    "url": "assets/js/26.d30159f5.js",
    "revision": "6b5c659ecdf0a2ebba678aef28bdbbb6"
  },
  {
    "url": "assets/js/27.b6610f56.js",
    "revision": "b692fcc119f454b4a125b612350f3601"
  },
  {
    "url": "assets/js/28.77725dcd.js",
    "revision": "00a478c0b59c86329d5c867d9588467e"
  },
  {
    "url": "assets/js/29.332ddcdc.js",
    "revision": "42ee87c680cb972eb27e9dd754c3b968"
  },
  {
    "url": "assets/js/3.1403d76a.js",
    "revision": "757de23b8e8f27a1afa4202e762fd69e"
  },
  {
    "url": "assets/js/30.f4f88a33.js",
    "revision": "fe188ccb9b9d55399830039bd200513a"
  },
  {
    "url": "assets/js/4.e29e4ea3.js",
    "revision": "7f64e478df09e495c18c09a5c5ebbf5b"
  },
  {
    "url": "assets/js/5.a19407d7.js",
    "revision": "4e3b2cef5cf1e797d153c9e6f4f67221"
  },
  {
    "url": "assets/js/6.044cb810.js",
    "revision": "48c738c427da079ff1670ee773b119a4"
  },
  {
    "url": "assets/js/7.16e71b1d.js",
    "revision": "d30f22d0aa5cb1fed2e21bd92431078e"
  },
  {
    "url": "assets/js/8.17b4be3c.js",
    "revision": "3e1ebe49f1e8a01a793adba6e54346ec"
  },
  {
    "url": "assets/js/9.159cf920.js",
    "revision": "38dcc1bf222fe0e64e0910706cb76c06"
  },
  {
    "url": "assets/js/app.4a7f6659.js",
    "revision": "557c1035ba97c4b6dced3339451469dd"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "730b193d742e90025d2b713e7ee8a5aa"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "85ea40a852b0f9c4d4fc7847cc07a9bd"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "d38429aec9bd8ed9af881ba4028fff92"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "35097b4f9ef1a9366e6759b47c629e5a"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "8747c8c71c340e9c023b72c8aa0671b0"
  },
  {
    "url": "en-us/Download.html",
    "revision": "c947959b673a384e8a8aff76dc382644"
  },
  {
    "url": "en-us/index.html",
    "revision": "957c1a3e8dc068f858d37b4b852d4377"
  },
  {
    "url": "en-us/Support.html",
    "revision": "23735d6869b5d19aa771bf2e90d89ce4"
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
    "revision": "a80f9d3c25dcef345962b148f03f21f4"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "c3bb91cde4ed8aeaabcd851ac5f42655"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "680d3c5a0618a386c3fa406dcb00f741"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "3a9c962c04da320c4b56a696db6b28f0"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "819909c844f3971fa25c24194d9917ed"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "77f78cd7369c0f8dea262f0c92dcc972"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "b294471c0b564e2c302a4bd38228975f"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "232ad6169cbd6759818b4d37e0ccc818"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "a69e9ae072b25826c2ddadca2669933c"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "74d182b1ad3c6a0fd4a885179652d8a4"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "5e0e1dd5d8665189bb22ff9d511cf55c"
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
