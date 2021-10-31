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
    "revision": "0f6830e62140588d1f1ba1a2f37190af"
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
    "url": "assets/js/app.b5ee91ab.js",
    "revision": "edc5919ba199eb8f9a1491e23fe95622"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "fc527dcc65b1218f91477bf5c63a6d74"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "a0ab5f12d1345772d12800384aa4e0a6"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "3beda383883d380a244190ac293581b0"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "43a9e22e16110fdd4bdf5647af64333a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "5aedbfaeae03383c8ff6feeb01f0cc9b"
  },
  {
    "url": "en-us/index.html",
    "revision": "9007c0db31203bc819cf1b5c0724ebb4"
  },
  {
    "url": "en-us/Support.html",
    "revision": "702e7633d72bcb877009f2d85df4832f"
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
    "url": "ru-ru/docs/Changelog.html",
    "revision": "a920828dabc93c80784a819028768b3c"
  },
  {
    "url": "ru-ru/docs/DevilMode.html",
    "revision": "b4b8f3b56009c1287622c407534bf23d"
  },
  {
    "url": "ru-ru/docs/index.html",
    "revision": "a919299ac8a053688753d07fc4ec43e2"
  },
  {
    "url": "ru-ru/docs/SharedLibrary.html",
    "revision": "d35e89c706831dd61a6b5a20629f91a4"
  },
  {
    "url": "ru-ru/Download.html",
    "revision": "e96bcbb6f974e98c7adb730ea5ab2521"
  },
  {
    "url": "ru-ru/index.html",
    "revision": "e564dfe0abaa7bde569dd27aa53a8052"
  },
  {
    "url": "ru-ru/Support.html",
    "revision": "bb36417589240eb10f82c207d5375825"
  },
  {
    "url": "zh-hans/docs/Changelog.html",
    "revision": "c47eb91515e556b48b2b5b499059f1c3"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "de1f1e4ca40fb324ef227f5e66cff761"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "91fa6d37d9d3392fec426aa7af0a6759"
  },
  {
    "url": "zh-hans/docs/SharedLibrary.html",
    "revision": "dc4c05442ee92d161eff0026e623748e"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "d8ceb197a1f9044e466c7744a792df98"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "534d338247c37e645d580f474f58adca"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "ea4c331fab7df47c7319af95e9222d28"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "cd679b83b1517f460aedb3802a87dd71"
  },
  {
    "url": "zh-hant/docs/DevilMode.html",
    "revision": "5455725a6763704967aed9e025109534"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "2c145dacabcf4737c2f651afb0ede6ca"
  },
  {
    "url": "zh-hant/docs/SharedLibrary.html",
    "revision": "be4a945b50235595d8b6603043c26d13"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "0b8f8a9217ef2885c55aedf62cae6321"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "458bc3c2fa213fbdb075a85313cfad3c"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "8277d8957fc60a7f065117f977c37aea"
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
