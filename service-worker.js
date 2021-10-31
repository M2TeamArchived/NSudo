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
    "revision": "425ef7a679f93680a64437af0fd07b0b"
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
    "url": "assets/js/10.c1334aa3.js",
    "revision": "f669fb759a18f6bf69ebe996f7ad76e7"
  },
  {
    "url": "assets/js/11.3b013d61.js",
    "revision": "3a90a7ad57de69315da1818b7c7d224c"
  },
  {
    "url": "assets/js/12.d9803369.js",
    "revision": "5f3167e2909baf07ce4825821abf46db"
  },
  {
    "url": "assets/js/13.2eaa09dd.js",
    "revision": "a48313657c13bc92dd653b3f886f4985"
  },
  {
    "url": "assets/js/14.a29e2f22.js",
    "revision": "ee28caa0abf45d77a50dba7c533fd356"
  },
  {
    "url": "assets/js/15.63f52631.js",
    "revision": "cfb0a3cadfc5022d8e4f678263c65703"
  },
  {
    "url": "assets/js/16.aa89e2d5.js",
    "revision": "3177b9dc79b48e20b4d7f96f52281fae"
  },
  {
    "url": "assets/js/17.6f516a21.js",
    "revision": "e8c65b278f2e8f73669dcfbbbe4224ae"
  },
  {
    "url": "assets/js/18.7dc4572a.js",
    "revision": "283e88ad092666ea09ffd642e3db461c"
  },
  {
    "url": "assets/js/19.d5593da5.js",
    "revision": "1a021da367de0e0a5fb88e5bfbc2cfd9"
  },
  {
    "url": "assets/js/2.05352310.js",
    "revision": "b492e70350d7fa3d7c2e6ff120b925fc"
  },
  {
    "url": "assets/js/20.ea4f2ff2.js",
    "revision": "658155b441e24c7cb63ae3f273584f05"
  },
  {
    "url": "assets/js/21.af30d5c1.js",
    "revision": "289fb23abff259537530a683530f86b0"
  },
  {
    "url": "assets/js/22.b2080267.js",
    "revision": "6bdb09fe45527ccc7867a27a18a866dc"
  },
  {
    "url": "assets/js/23.1d6b7eb9.js",
    "revision": "98e1252e4f53fc03d6f4118b14462709"
  },
  {
    "url": "assets/js/24.5d451d56.js",
    "revision": "b6bc32f2a2d29360ee6d01af0bf5854a"
  },
  {
    "url": "assets/js/25.1698b236.js",
    "revision": "19ad49ddbf48b7ad9cd14c615b1a0222"
  },
  {
    "url": "assets/js/26.55fd2c6a.js",
    "revision": "6735ee4ad782ca0c787c05e988ef4f41"
  },
  {
    "url": "assets/js/27.42621399.js",
    "revision": "c3aadc848cf39b01498f8d1cbbd32f61"
  },
  {
    "url": "assets/js/28.44a663a5.js",
    "revision": "9c63cd1c4bbf05009c09241fe4244d68"
  },
  {
    "url": "assets/js/29.e124c300.js",
    "revision": "dc6b17231ef5c205c2df73c81f4f67c0"
  },
  {
    "url": "assets/js/3.a8b8f3e7.js",
    "revision": "1a1aa8869da82658f874c118c02dde2d"
  },
  {
    "url": "assets/js/30.ebb957d0.js",
    "revision": "3fdbdd16298b829e02965b9d4e29d628"
  },
  {
    "url": "assets/js/31.8605ba75.js",
    "revision": "583629b4f6032c14b3af45adc4106a8a"
  },
  {
    "url": "assets/js/32.f3e58288.js",
    "revision": "0ee049bc1520ba49c54457d19a3a0727"
  },
  {
    "url": "assets/js/33.97af0daf.js",
    "revision": "29e67f04c5bb828a5f7fa9b118955f32"
  },
  {
    "url": "assets/js/34.71b5038b.js",
    "revision": "e7231d537ffa19860b66b4459e9e6efc"
  },
  {
    "url": "assets/js/35.f5b4bc51.js",
    "revision": "83a0a68c709bee5214d5554fc0e0269c"
  },
  {
    "url": "assets/js/36.df741252.js",
    "revision": "df1d94f19f05178730783bff1e4fea27"
  },
  {
    "url": "assets/js/4.a55e354e.js",
    "revision": "f6a02b81c273828c648eda5ae332be52"
  },
  {
    "url": "assets/js/5.6e7d2058.js",
    "revision": "9d598f7b73dd6e2172945b3b595d3bea"
  },
  {
    "url": "assets/js/6.9f4ba975.js",
    "revision": "14396abed9fd065ee0714ce297ee796c"
  },
  {
    "url": "assets/js/7.4bcec110.js",
    "revision": "eba692f9dbf5471952afceb346ea9c81"
  },
  {
    "url": "assets/js/8.0d24e5fc.js",
    "revision": "01e1971bb8edf7d60f18abd586294cef"
  },
  {
    "url": "assets/js/9.028c78b6.js",
    "revision": "e80edd5531aec0c6695e14442a765c05"
  },
  {
    "url": "assets/js/app.a55de235.js",
    "revision": "9acafd1d4b382dbbb584e63be76bedeb"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "0f13d0f8193caa75236efff462e3c038"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "1b346d55a5c671e34fec3cc4a40aca71"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "9deb76e81143bf2153be16b045b0cc5b"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "47c886726b81a7f2828a49e9bb8d039d"
  },
  {
    "url": "en-us/Download.html",
    "revision": "699a09a8710a39b2f2cc434343b0a6ea"
  },
  {
    "url": "en-us/index.html",
    "revision": "d789a98838b64113c044d90e0fd1a555"
  },
  {
    "url": "en-us/Support.html",
    "revision": "305188af461fe6cb570d8fd6b3380f69"
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
    "revision": "ccb0e7e0480dda24bffe69dd65f4c7ed"
  },
  {
    "url": "ru-ru/docs/DevilMode.html",
    "revision": "d635e371f5049ca40eb3b8a3f0b1cda8"
  },
  {
    "url": "ru-ru/docs/index.html",
    "revision": "5cff90626b73c10f5c555ba0b0763b7a"
  },
  {
    "url": "ru-ru/docs/SharedLibrary.html",
    "revision": "bec53927afd5453686463f3140c10964"
  },
  {
    "url": "ru-ru/Download.html",
    "revision": "7995affdad19a75e939f00b6201a9af2"
  },
  {
    "url": "ru-ru/index.html",
    "revision": "cbc757fb91a5858f97c2cd7d04ba247f"
  },
  {
    "url": "ru-ru/Support.html",
    "revision": "b7216fbafe8f19114ab07282db8cfe49"
  },
  {
    "url": "zh-hans/docs/Changelog.html",
    "revision": "043ddd8537afa7205f5c9b8ac551e7e0"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "f6fd5b451427dbee50f30c04edd5827f"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "c156bd8b0fbf384ed1cf5b3f775ff71f"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "d2a7dea402eacf049661b2314a1b7737"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "e41fc33e1c9432c784cc4b98392d4fad"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "bc4f09953c28e5e6eb709168c5f4f622"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "cae737041f36b5798ee6d3858137d68c"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "d43248addaa4692b962488f59987717f"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "82921e85990b8c296c7f59616aa7d02a"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "540e24943bb550a630d8ff507170653c"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "63e162c063c7ae68371f5829b1850c3b"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "604cf65d2ef64051ab3c5c15b0165c66"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "d4168eb1f727926f0e27bc8f581f3ca9"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "fe0c52fdc954c8b0627a53df5073a9da"
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
