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
    "revision": "c8ae9881f3e1b9f2eef4b34fad71236f"
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
    "url": "assets/js/15.f3de8a7d.js",
    "revision": "bfdc5e677f9c735e6d8b61dcbd26c625"
  },
  {
    "url": "assets/js/16.4fc99bd4.js",
    "revision": "cd287d1201fda3633c284606e024c5b8"
  },
  {
    "url": "assets/js/17.d29fc59f.js",
    "revision": "4842ea2a0861502c3d90646e11d27a1e"
  },
  {
    "url": "assets/js/18.1f7d08dd.js",
    "revision": "c0eef52a3e681fed33d0ba258a29edbb"
  },
  {
    "url": "assets/js/19.36d03c63.js",
    "revision": "700de8020b970788bb18fa8ed696e4fe"
  },
  {
    "url": "assets/js/2.93082767.js",
    "revision": "ef50228e22a74d3542d8b4f6bf9c9003"
  },
  {
    "url": "assets/js/20.4b0a115a.js",
    "revision": "69576f452825917b51f363ecff8ff16f"
  },
  {
    "url": "assets/js/21.bde0ac30.js",
    "revision": "346ea1e079f67e59cc11e4148be843b3"
  },
  {
    "url": "assets/js/22.69e5ca88.js",
    "revision": "a75b9ea4f386ed4b3ad03be0bae07e5f"
  },
  {
    "url": "assets/js/23.d24e5a0d.js",
    "revision": "03849fb4e889d296f8765f49677d3a39"
  },
  {
    "url": "assets/js/24.353afd32.js",
    "revision": "d72da84573d27a57468a23db1d96e9e2"
  },
  {
    "url": "assets/js/25.2f542a94.js",
    "revision": "1a2862aef06251809f5ea5e6d2793bfa"
  },
  {
    "url": "assets/js/26.e3b60992.js",
    "revision": "749ae7490c0732437aadb701dd09eb39"
  },
  {
    "url": "assets/js/27.5426d9aa.js",
    "revision": "5d43fefd96549ec082da5d2f4d24c30b"
  },
  {
    "url": "assets/js/28.a664bfe4.js",
    "revision": "c2d3945a583e2a1dc9a501a1546bb6bc"
  },
  {
    "url": "assets/js/29.dff03c1b.js",
    "revision": "3911b5078bb5c6ecf89c4f9521e50ff1"
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
    "url": "assets/js/7.6f45158b.js",
    "revision": "3416708472f8215c3ec978e4d438e091"
  },
  {
    "url": "assets/js/8.2362bbc9.js",
    "revision": "0cb301d2fbbe9a784834200afeae5e47"
  },
  {
    "url": "assets/js/9.48a19368.js",
    "revision": "597288235609952a228b741359a6785f"
  },
  {
    "url": "assets/js/app.3af45e89.js",
    "revision": "5330258103f2291afbce99654758c878"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "41e84bf6ce0c2128c6b0068ba223a89d"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "1f3facfed8f8045cc5a2696a8e3e4c3e"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "53a48b68729fbcc75de123710adac05e"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "464a6915d1cade192854aa7565d35ef1"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "9d68c18c67a449e260207ce29542c561"
  },
  {
    "url": "en-us/Download.html",
    "revision": "8f21b4ab15e80b4bf543bc62855fb07e"
  },
  {
    "url": "en-us/index.html",
    "revision": "e48e1e0cef4954b136ceb5eaf70122fc"
  },
  {
    "url": "en-us/Support.html",
    "revision": "fb6a7481ae70f8dba7f0715b35342544"
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
    "revision": "d12eede5a28e1bbe9e9ce9672a121027"
  },
  {
    "url": "zh-hans/docs/Changelog.html",
    "revision": "df5a6f774c8024523744447abbcfbd95"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "278ee9ea5986bb99f3476535a5ed5d98"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "7f453cb3748c2fc8f497bca2e30faf6f"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "b6febb37944f79acb103f07c1b32f9ed"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "baabaa4ccf1d62a73ef2e22d7bc6a607"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "df8e38f71023a2608928e5750bab8a1c"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "ba340fec56548e6415f2d0668b9ff6d0"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "e84ddc6d9540628815e03f01d39867a4"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "9c04b5aacfb468384e4c0d4fef8017aa"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "f109468b53116f71ace7a8243d545842"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "a5262db9a7a90c1e7507c0e8ce1d5d90"
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
