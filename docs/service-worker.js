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
    "revision": "4e83cf3ed79a0a76568e40483a5a67b3"
  },
  {
    "url": "assets/css/0.styles.abe3edf1.css",
    "revision": "2cfd080599dc01ade4f3df23ba2df5af"
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
    "url": "assets/js/14.d0cd45d3.js",
    "revision": "f8ed3f7efc09776e209e251c4f98a8d6"
  },
  {
    "url": "assets/js/15.76feb162.js",
    "revision": "6b5101cb4c53e62b4c669b6997e1aed5"
  },
  {
    "url": "assets/js/16.4fc99bd4.js",
    "revision": "cd287d1201fda3633c284606e024c5b8"
  },
  {
    "url": "assets/js/17.7067dd00.js",
    "revision": "f011b912ea53f39a0b874bcf320bd48d"
  },
  {
    "url": "assets/js/18.ccd2bf4d.js",
    "revision": "ea6011c1fd02f0b276f89ebb955005b6"
  },
  {
    "url": "assets/js/19.f88e7fd8.js",
    "revision": "635b3f3b982a9bc1d1aabcfe7abeda69"
  },
  {
    "url": "assets/js/2.93082767.js",
    "revision": "ef50228e22a74d3542d8b4f6bf9c9003"
  },
  {
    "url": "assets/js/20.3315de44.js",
    "revision": "610c218dbac740dd4932fb32386f0ffe"
  },
  {
    "url": "assets/js/21.9cc5d977.js",
    "revision": "b9b143511c55a3cccde4595405b826ca"
  },
  {
    "url": "assets/js/22.c6f066a4.js",
    "revision": "6ed9e3dae09a633d32579fb0512d3e6f"
  },
  {
    "url": "assets/js/23.3229c78d.js",
    "revision": "3803824f416cb2986b769af4508321df"
  },
  {
    "url": "assets/js/24.78f98920.js",
    "revision": "d17852d42e58f8fb3c4de8548af72f55"
  },
  {
    "url": "assets/js/25.d73d9c39.js",
    "revision": "0becbe39efae954bce5d86a6149d3b6a"
  },
  {
    "url": "assets/js/26.1b3844cc.js",
    "revision": "c437bcf6c073ab87719cc9156e930a68"
  },
  {
    "url": "assets/js/27.b6610f56.js",
    "revision": "b692fcc119f454b4a125b612350f3601"
  },
  {
    "url": "assets/js/28.4afb2306.js",
    "revision": "f6d2bb805a6ce339ed81f5487f8d3d95"
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
    "url": "assets/js/4.5268512d.js",
    "revision": "cc25dcd43556477ad33a630a19653a41"
  },
  {
    "url": "assets/js/5.79e6b7b3.js",
    "revision": "3cbcb1309ade81d0d0eb4eecbdaf74ae"
  },
  {
    "url": "assets/js/6.044cb810.js",
    "revision": "48c738c427da079ff1670ee773b119a4"
  },
  {
    "url": "assets/js/7.ea5f0c52.js",
    "revision": "fe43dc91c15ff310d03f48503fbb387a"
  },
  {
    "url": "assets/js/8.0b8b0e1c.js",
    "revision": "a5831be1cc66f4821ebb35c720c2e984"
  },
  {
    "url": "assets/js/9.44d80052.js",
    "revision": "12df8e5fa002691c1c4c758e9b8b2ced"
  },
  {
    "url": "assets/js/app.ea58b3cd.js",
    "revision": "30d7a4f58cd1d528d1ad80a576b976c3"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "8028ed9dc55deb8b3ac6a2c9c339f42c"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "384ac7684d17df1f9d20430690dfada7"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "d290f286881662aa7bcb6c9dea54a93f"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "bdaf9177188f206568f6006e868b98e5"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "5119cee6cfd9b95bdc5b1649c5ea81c2"
  },
  {
    "url": "en-us/Download.html",
    "revision": "4f97237b07a7b7c5efb50ecc7181ad7c"
  },
  {
    "url": "en-us/index.html",
    "revision": "386e559dfafeef6b8e822238ba22ba1b"
  },
  {
    "url": "en-us/Support.html",
    "revision": "6ba814e85cbffd12d91615177bcd8ee7"
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
    "revision": "ae3fb48652b0bafd2b64e36426386850"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "73ea6d1279b92d4aade6bfd4f761830d"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "c5387dfbdebd6d98ce57c00cbd4c36e0"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "152101685300f2a2e1864f030080dbfa"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "c81caedb73fb22131e5c796bccb519b6"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "4294428582dbd304c89aa89c4df6bb54"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "7aac8a9df48edf33f73da7fe660f626e"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "9f47b85b51816949a3915e83546fd6b7"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "11792b0245e15761a8a93782242f3b07"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "f32dbd6225398ffc218d002abb7128ad"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "18f6eefee7de03adad631314d3f612b5"
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
