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
    "revision": "a95884ca21716fd5aca40fe020282023"
  },
  {
    "url": "assets/css/0.styles.c221087a.css",
    "revision": "31f70f717d2c31b18086c2330a53438e"
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
    "url": "assets/js/10.1aae8263.js",
    "revision": "4f93a7f9123fbbc3bfc543d2342cb180"
  },
  {
    "url": "assets/js/11.dec86705.js",
    "revision": "ef8c4fa28301eed2705ba98641c53003"
  },
  {
    "url": "assets/js/12.8b87b02d.js",
    "revision": "d0d1ff6a90fe67111becf02e2d6537d8"
  },
  {
    "url": "assets/js/13.c606b6d2.js",
    "revision": "9962fe3b6e8197753fedf50d929a2ca2"
  },
  {
    "url": "assets/js/14.3939203b.js",
    "revision": "480351935258a23551a207e23c1f70bc"
  },
  {
    "url": "assets/js/15.b0034f69.js",
    "revision": "92108ea8fb7abf5d21b78ba8e67b2a6c"
  },
  {
    "url": "assets/js/16.32685515.js",
    "revision": "bfef19e046d38bd6a40c58a6e41cddc7"
  },
  {
    "url": "assets/js/17.df17c4ba.js",
    "revision": "3b2577563d24993835a560e8365eeabb"
  },
  {
    "url": "assets/js/18.22aaadd7.js",
    "revision": "77622d50a5b3a610997a6ac9dfedda7e"
  },
  {
    "url": "assets/js/19.5c4d7f70.js",
    "revision": "af75324887d2d45b04c225fe0b5e9e0a"
  },
  {
    "url": "assets/js/2.070eee7d.js",
    "revision": "bd3c547fabc31436d7f2e7f9b757e67d"
  },
  {
    "url": "assets/js/20.d3f77588.js",
    "revision": "fbb0d68b51567f83229932f1815bf856"
  },
  {
    "url": "assets/js/21.f5a16991.js",
    "revision": "e242f2c3030f7b7fad85ba77c3525042"
  },
  {
    "url": "assets/js/22.baff50f8.js",
    "revision": "57ed95b30fb1e264e68a410ca2115990"
  },
  {
    "url": "assets/js/23.2a466711.js",
    "revision": "ea16b7986da0116a5bdeb1206ad433dd"
  },
  {
    "url": "assets/js/24.c7d3ecbe.js",
    "revision": "41a029815b7cddf5d19f008fb645a885"
  },
  {
    "url": "assets/js/25.a4fabe36.js",
    "revision": "bd577d21e6b05a04a4dfacaf6c41be46"
  },
  {
    "url": "assets/js/26.b4a4cb61.js",
    "revision": "f865807eeed9f499dbe380bad6224621"
  },
  {
    "url": "assets/js/27.2f7055f5.js",
    "revision": "9839105c7bd87890fb4fa8ae5ccd3083"
  },
  {
    "url": "assets/js/3.85e1b9f5.js",
    "revision": "ed06a093ee3d7a061472b6b828e40dc7"
  },
  {
    "url": "assets/js/4.5268512d.js",
    "revision": "cc25dcd43556477ad33a630a19653a41"
  },
  {
    "url": "assets/js/5.1c04e83a.js",
    "revision": "5cfdf306ca7f5c4940f1f70ba8d953a6"
  },
  {
    "url": "assets/js/6.fd86db85.js",
    "revision": "6fbbdfc045cba9d5027aee0fb39fd4b0"
  },
  {
    "url": "assets/js/7.4bf08af9.js",
    "revision": "8a6bbe6dc4d8ac892f2c378407f798bd"
  },
  {
    "url": "assets/js/8.432bba91.js",
    "revision": "1ee931069b42be8194c19389a253341d"
  },
  {
    "url": "assets/js/9.7130cfeb.js",
    "revision": "06216c95ca61c2c6430f042800a26de6"
  },
  {
    "url": "assets/js/app.95650cfd.js",
    "revision": "15f3749451d1e8f1453dab4eee92666c"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "7389e9338e3afea344d8ae27f08a7603"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "c2ac36ae149112a1707079401dfb3a58"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "dcf6e73cbc77bd6f3279b247a6ab4236"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "912c0730dad5629ef1ca7e1f5900d9ca"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "e9aea6029b472fef27bd431b4f94db1a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "d66b75b72f2ed612b76ad695f81b1665"
  },
  {
    "url": "en-us/index.html",
    "revision": "eab64629593af3fee433eca5c26e5901"
  },
  {
    "url": "en-us/Support.html",
    "revision": "6c05e1f8e5adbcc0acc61f3221c45161"
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
    "revision": "1bc9e6daefca99a1286476f58bcf749f"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "e092143ac6d69851c8caf1eb41110f26"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "b66c730924cbed637ed2a2807676136b"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "a26a69ee64ad0dba8158a18ef5e02513"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "cd3392d53aa3f1820dc3402139ba799c"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "be764676a9703d6e28be4c803da2fc5d"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "6cff3557a51e37241aca0219297097ab"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "b25ac1967ffed9dbc583e83056ef8759"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "89d83a5fe50470797c38e0c67446d8f2"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "54170e868ffce9952f4689db869eb192"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "efbac3f773d25fa3c370a08a76f9031d"
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
