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
    "revision": "7dc0fb8be07e3eacebfcc11fe9e4af81"
  },
  {
    "url": "assets/css/0.styles.0cc90dfa.css",
    "revision": "d186c4301a5a452f6b47d9af145c8651"
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
    "url": "assets/js/12.4b92635a.js",
    "revision": "4b2f8095b5490ec92666505311365c69"
  },
  {
    "url": "assets/js/13.8bee48cf.js",
    "revision": "477b1798670bac117bc838c40a51594f"
  },
  {
    "url": "assets/js/14.4a3b0c19.js",
    "revision": "7a2fb08862c431de8fdd8a691e24193f"
  },
  {
    "url": "assets/js/15.a8b9bba9.js",
    "revision": "964c8710b38582571adc15746ebf6ada"
  },
  {
    "url": "assets/js/16.4ae7c1a0.js",
    "revision": "c92c5a0e39f5b5695ac4aa0c07036f50"
  },
  {
    "url": "assets/js/17.df17c4ba.js",
    "revision": "3b2577563d24993835a560e8365eeabb"
  },
  {
    "url": "assets/js/18.06721427.js",
    "revision": "6735311d0e1fb2cd983d57c585590260"
  },
  {
    "url": "assets/js/19.46bb8b7b.js",
    "revision": "f8b8afb6d0de76207905ec6832104cf3"
  },
  {
    "url": "assets/js/2.070eee7d.js",
    "revision": "bd3c547fabc31436d7f2e7f9b757e67d"
  },
  {
    "url": "assets/js/20.f72fd379.js",
    "revision": "44afd2ee21191d7513c68fa45e2144f6"
  },
  {
    "url": "assets/js/21.d2f00f33.js",
    "revision": "25c84088dfe9cee06956af8618449dcf"
  },
  {
    "url": "assets/js/22.52523779.js",
    "revision": "d268e04f142face3138a2a2a309fed42"
  },
  {
    "url": "assets/js/23.2ec94bc1.js",
    "revision": "356721530b03002142a0fd7a4188aeb0"
  },
  {
    "url": "assets/js/24.4a5d3664.js",
    "revision": "d3082a813da27236a164c5eb2c5f60eb"
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
    "url": "assets/js/8.c6029e12.js",
    "revision": "23c7c7bb4f03a38bc91235f4581e6656"
  },
  {
    "url": "assets/js/9.c430fcf0.js",
    "revision": "e8217c04ffe5108394d203d024ea3db3"
  },
  {
    "url": "assets/js/app.ef75a841.js",
    "revision": "2f1b704264f6b02617b4a9deb4eca504"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "9e3cb13601f15e0a2399d670fd61f4f7"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "799b72b0d8d71e844d63088050d3164a"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "b7ed06c56c934f854cfa6cb5778cc745"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "e965ecd88fd53800fd5443a802e8ae27"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "c7ac4be05a6e21929f8526112267eb70"
  },
  {
    "url": "en-us/Download.html",
    "revision": "f5aca98dc89ffcb28732a3f0a904117a"
  },
  {
    "url": "en-us/index.html",
    "revision": "79328cb3f9a8f5f6b5659eeb127cdd3e"
  },
  {
    "url": "en-us/Support.html",
    "revision": "401ffeefc272328d7f5d7c6254e26eb7"
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
    "revision": "e3696de85b29ee90f90c98712787c9dc"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "966a4d72daa5eb5da31b68ad645670ad"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "bdab95eb92e66a5e3df6da2a539cc0dd"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "45123e14f427b23a000225a2b59df211"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "477bcdba19d9fc9767500a958830a038"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "5550d029642b934bb2dc5b614e8f935e"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "d047188e23119bf59aa31fa431b297f0"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "2d4d11283e72e0d833e9b45274f102ad"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "42c04bcc62f20ce3d1cdf5aa82d40e59"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "5b3ed759f76bafa8ef75431206818f36"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "f0066968fcf22ba7ea5ef48c4d541547"
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
