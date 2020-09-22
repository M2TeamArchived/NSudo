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
    "revision": "bf7166192fa23c293b5dd5b4b7fbdb33"
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
    "url": "assets/js/12.5e7b7c22.js",
    "revision": "4bf89dd2783219776607be4fdadbbfa8"
  },
  {
    "url": "assets/js/13.b9c80857.js",
    "revision": "b35bd45f298ae2e18cef18e65ca6da7f"
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
    "url": "assets/js/23.edc8f48b.js",
    "revision": "5ea789c9a9b6d9474148263ec2ea7eef"
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
    "url": "assets/js/6.ed08e112.js",
    "revision": "03be0610e4967a45c86bb7d38723eceb"
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
    "url": "assets/js/app.c34a7856.js",
    "revision": "2b15c5a1aa82a4dda6a2f759cdae0421"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "a43c02a72da5774f8cbdeaf2447cfc1c"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "950662a5a3cb1d4dbca54953920f3201"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "8e9836100cc6b9cd01fd3a10c2b213e2"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "aeb32b2123a20e76cd85dc7dcb364f88"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "5acbcb2e9da9a7d68a97cf6568fd3fb6"
  },
  {
    "url": "en-us/Download.html",
    "revision": "c2d644390cc1baa8917a685f1119d81f"
  },
  {
    "url": "en-us/index.html",
    "revision": "d57362218006bf5f2ad76b3de8760165"
  },
  {
    "url": "en-us/Support.html",
    "revision": "362adc61eab305f5e9f26031471f0343"
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
    "revision": "c2b14293121d22505c64f51810b8585a"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "a5083d68745601401300749db4a1b289"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "4c1f54324b54e6dde00dd77abe62525c"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "318215008baf69a0640788e5505151fa"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "18784fe72511bec81d034dd91d6ad592"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "cc6e93ec4aee89028c9839c62f0c76c1"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "bc98396f2fba05bdbc201500c74bde19"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "4a071b4c9598bbaaed62ef222d2df180"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "cf58aa2dbe63ec0716db34df10a5d7ae"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "4784f1ce8ceeb155a9aa5505a732d2ac"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "a51075125b7a5d551a4987682d493acf"
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
