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
    "revision": "6c65541f742df41486d28af1dbc0fa56"
  },
  {
    "url": "assets/css/0.styles.4d5cd2b1.css",
    "revision": "ebeaf74cc5fd56a714968fc30ded6731"
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
    "url": "assets/js/10.ef197e87.js",
    "revision": "b5975143a2158fe58ec40796c37e24f6"
  },
  {
    "url": "assets/js/11.93d8e253.js",
    "revision": "aa556e254864280fb6a8d615c5fbd643"
  },
  {
    "url": "assets/js/12.58db3ac4.js",
    "revision": "f2f5f0b02ac09af971c30916116aab01"
  },
  {
    "url": "assets/js/13.b5db69ad.js",
    "revision": "3e0e72c9bdb9445be66383c3beaaeca9"
  },
  {
    "url": "assets/js/14.3939203b.js",
    "revision": "480351935258a23551a207e23c1f70bc"
  },
  {
    "url": "assets/js/15.5774c73c.js",
    "revision": "f945e7ff16ad2113539228dcaf0b16ee"
  },
  {
    "url": "assets/js/16.2c7253f2.js",
    "revision": "5e223955a2dc960533ab443a3bbfc4d8"
  },
  {
    "url": "assets/js/17.1f759942.js",
    "revision": "0e4da30623580387bf3ec3025e140d12"
  },
  {
    "url": "assets/js/18.98824e00.js",
    "revision": "5324fb654b361a071704ceaa2254e40f"
  },
  {
    "url": "assets/js/19.418c54cb.js",
    "revision": "e1a0c8f087c9ea677fd39c895e30dbbe"
  },
  {
    "url": "assets/js/2.e2791b4b.js",
    "revision": "d3b71fd9e010e43a93b59fdf36f065eb"
  },
  {
    "url": "assets/js/20.0e27a0f0.js",
    "revision": "c10507e47fecefbfcd9a484e7f5d41f4"
  },
  {
    "url": "assets/js/21.6b074433.js",
    "revision": "8e8942adeae3085f1f983b4bfc3b0350"
  },
  {
    "url": "assets/js/22.52523779.js",
    "revision": "d268e04f142face3138a2a2a309fed42"
  },
  {
    "url": "assets/js/23.a9bef035.js",
    "revision": "da439ddbb3237a75a7bfefd89f1207e2"
  },
  {
    "url": "assets/js/24.c7d3ecbe.js",
    "revision": "41a029815b7cddf5d19f008fb645a885"
  },
  {
    "url": "assets/js/25.1ef5ef87.js",
    "revision": "56e13accf86cca5968c0f8769de75f8c"
  },
  {
    "url": "assets/js/26.46197876.js",
    "revision": "b10a8575fcdcd4cb1c2485da6d18bfed"
  },
  {
    "url": "assets/js/27.0dbca146.js",
    "revision": "66f7a8c14f6dd638b6f81c2bb2997edb"
  },
  {
    "url": "assets/js/3.2cbfa41e.js",
    "revision": "e8d5e567044c81c33e6d44b5afd6c0a1"
  },
  {
    "url": "assets/js/4.bdeec29a.js",
    "revision": "2229bcb74bbc57f04ad7c6bf66c3d492"
  },
  {
    "url": "assets/js/5.64fcc124.js",
    "revision": "bc37992b0e744a51968b8056cfbfa89c"
  },
  {
    "url": "assets/js/6.e29457e1.js",
    "revision": "6be76da2134b0c4e15d882c65da07237"
  },
  {
    "url": "assets/js/7.27702014.js",
    "revision": "b02bf46bbbdc87543eaf1bb309a99d9f"
  },
  {
    "url": "assets/js/8.282f9921.js",
    "revision": "12bee5099b431fc82c81408ee6f11636"
  },
  {
    "url": "assets/js/9.198b4ff0.js",
    "revision": "03a7542b8257bfd0d237c334d2b10cc5"
  },
  {
    "url": "assets/js/app.56d78460.js",
    "revision": "666b02d78d93e8202533c850e39a2d16"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "cb6600affa3eae0dbb48a8c9d237cc4e"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "9c20f7a9d7669d011ee404808a9ec205"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "5232a8422cddad62b971efcaa2171c8e"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "70175162b060bc31c6640e6ff5d7a9a8"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "353c9c483d3e6517a0b22c1810fdb35f"
  },
  {
    "url": "en-us/Download.html",
    "revision": "93d8bc6f2caccd0ef66f387fb1c74d25"
  },
  {
    "url": "en-us/index.html",
    "revision": "dfd7f6218c7a661cc41097c6f056b9dc"
  },
  {
    "url": "en-us/Support.html",
    "revision": "e8092e2295b77f42e79d364417b6e0cd"
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
    "revision": "71261209489add4f7423bec5df85ebd0"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "be047749a39ff0f41b66f95066aed6a4"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "617c5d41f13d6029f92927fb7dc9fa95"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "cb2208aa35791821b6c2c9ea64fbcfa8"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "69e2dc0c283489212404cdf377d1c65c"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "7cc3732c8c380953072d565ff281cac9"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "39d8a43ef40dbb7019c9a7bf2044cfda"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "8c032c7789cb1088702131caab977161"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "0023e9c2053c4fb7d6a519b796534de9"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "5b7e911374edca2d547f5889060cbbc6"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "577663df9d4c20ebd574ae2e59d7d00d"
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
