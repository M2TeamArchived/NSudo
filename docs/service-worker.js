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
    "revision": "f71f9d8aed380beb8790cf311ade723a"
  },
  {
    "url": "assets/css/0.styles.4f449895.css",
    "revision": "ab0eb244a2689636c6a38d61a9e30860"
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
    "url": "assets/js/10.69aa4e59.js",
    "revision": "3e050063c3779ae42a40aeac8868787e"
  },
  {
    "url": "assets/js/11.89cb31c2.js",
    "revision": "70af00b9fb96bb605de6164edd8ba7c4"
  },
  {
    "url": "assets/js/12.0d5676bc.js",
    "revision": "e786891a4263ed2e6ec5af859ff65c59"
  },
  {
    "url": "assets/js/13.90b2264e.js",
    "revision": "3dc5279e05a0c2dba80b65ea57297ee9"
  },
  {
    "url": "assets/js/14.99369952.js",
    "revision": "300b3dee9603802cda8239c9b1cc33b8"
  },
  {
    "url": "assets/js/15.05241808.js",
    "revision": "565c996c43466aa52e8cc79ad61fba07"
  },
  {
    "url": "assets/js/16.55a4f13f.js",
    "revision": "6ee1b5653eac1ed2fc7b9711e81a8f9d"
  },
  {
    "url": "assets/js/17.7f497b2d.js",
    "revision": "1e4958281106239d4ae715d7a1fd1584"
  },
  {
    "url": "assets/js/18.6b657187.js",
    "revision": "703772a22c92affcd893b80a21aabed1"
  },
  {
    "url": "assets/js/19.48ad65d1.js",
    "revision": "d03f0d8eb909768b3141cf8d83b6e1ae"
  },
  {
    "url": "assets/js/2.d617e34c.js",
    "revision": "2242405c859b84f93da77b105535f030"
  },
  {
    "url": "assets/js/20.2648047c.js",
    "revision": "5b3606794f1f2f41c5b5b651b43a0a63"
  },
  {
    "url": "assets/js/21.a9afc3fb.js",
    "revision": "732cfd6be73bddbce0ae83965d168a18"
  },
  {
    "url": "assets/js/22.6be9f2ab.js",
    "revision": "f7324d4a224d3b190775a5f3d7fdef67"
  },
  {
    "url": "assets/js/23.cf34d2d0.js",
    "revision": "8d2dcd4baec0d8a92f570e718b2972f0"
  },
  {
    "url": "assets/js/24.34184a7f.js",
    "revision": "e4e69e3f407f5c2357d4b9e11ac73dc7"
  },
  {
    "url": "assets/js/25.1cf392ef.js",
    "revision": "90cbc02ef72bcdfd1afbe6e876083f19"
  },
  {
    "url": "assets/js/26.211c075d.js",
    "revision": "9bc6cfa158018344bafe84a993574e73"
  },
  {
    "url": "assets/js/27.8fefda9d.js",
    "revision": "c6007f099f1caa03dc8a2c561e29df8c"
  },
  {
    "url": "assets/js/3.538959b8.js",
    "revision": "96f314d0937aaa49da64e173b6094b84"
  },
  {
    "url": "assets/js/4.94f832d8.js",
    "revision": "0370334cd71f0b58101bc2243a7c3170"
  },
  {
    "url": "assets/js/5.309dee80.js",
    "revision": "c4dc3efbcb08c25ba824cdd5a509b8ea"
  },
  {
    "url": "assets/js/6.d290ac93.js",
    "revision": "c8dea6ec38c308952bb37fca4247179e"
  },
  {
    "url": "assets/js/7.fdd23fd0.js",
    "revision": "da11fdfc5a5625a744956250a4e257c9"
  },
  {
    "url": "assets/js/8.82ff13a0.js",
    "revision": "70e1af0a0a9d357565cdb4c635fe6db8"
  },
  {
    "url": "assets/js/9.77aebbea.js",
    "revision": "ddcc31a3c92074c97e3d7a51e9e337a6"
  },
  {
    "url": "assets/js/app.4fd42ec2.js",
    "revision": "59628146b8b37be1257234aced73a830"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "9a63c063c987d61ec41fa46995f0c765"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "4413c2b5ddb637383b3afd2d852c7207"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "5dd7302c5ea309eaaac98a226473dd25"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "a4ec95cc88e9c1bb952c4b1c33e93d27"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "3cbb68160b862d624312e30db2ef679c"
  },
  {
    "url": "en-us/Download.html",
    "revision": "327b722346ebe35394af6013f8a06e4e"
  },
  {
    "url": "en-us/index.html",
    "revision": "ce29cd2a264fa0b6078d167901cd23d4"
  },
  {
    "url": "en-us/Support.html",
    "revision": "af9c2ebf6e77e0984ee602a6c4669ddb"
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
    "revision": "d5c25aa6b06cac2dd6d8022b206c9d0e"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "9b8a72af84508259e792560c66b32928"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "261e87d87ddda5b3a1c95f91d42005c0"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "4d41ed7efde277bc861dc03eda2eac8e"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "9a872726f0a4dd0be048c48ce2bd849f"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "5cc4002c5186c879e9e4b1b0c4d9a6cf"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "89c1da98efae01c2e1e66a898f376d8e"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "536aa60e7d7087166542be281eebf901"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "259930da37e6e3547bb40b6514380c02"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "5404087dcaab15eb62fe9492fe291cc9"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "a8d7ef584d61517d493c704609c5a51e"
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
