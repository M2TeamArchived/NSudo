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
    "revision": "4b6f0d77bc8848a2bb377e8ddc730805"
  },
  {
    "url": "assets/css/0.styles.e74790d9.css",
    "revision": "224bdb7dec495cf2c11538d9fea1a889"
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
    "url": "assets/js/15.d953601f.js",
    "revision": "61e176b3130fce4c35b6b5abed642ebd"
  },
  {
    "url": "assets/js/16.7f6b0ecb.js",
    "revision": "98f87327abdc2557a8922fa8fa1de8f9"
  },
  {
    "url": "assets/js/17.4c59bd53.js",
    "revision": "40f144caac70a6acf8281b2392f08ab0"
  },
  {
    "url": "assets/js/18.5f0dd6ca.js",
    "revision": "391a8d399a384d79a9267de88abe5456"
  },
  {
    "url": "assets/js/19.36d03c63.js",
    "revision": "700de8020b970788bb18fa8ed696e4fe"
  },
  {
    "url": "assets/js/2.bc8bbda9.js",
    "revision": "ef50228e22a74d3542d8b4f6bf9c9003"
  },
  {
    "url": "assets/js/20.9b2b65f1.js",
    "revision": "0da7359d2026be80d77d8520693e9392"
  },
  {
    "url": "assets/js/21.bf258fa1.js",
    "revision": "a11aaf5621bdf21b1c217df86360ad8e"
  },
  {
    "url": "assets/js/22.96f2d432.js",
    "revision": "b85e493dde8e19d480cfafb2a6673aa9"
  },
  {
    "url": "assets/js/23.00e39da2.js",
    "revision": "54a1f7b168ca3f9d288a7cab5c2b4dd2"
  },
  {
    "url": "assets/js/24.82fdc4b1.js",
    "revision": "047ffa443720a07c846919b9ec570aa7"
  },
  {
    "url": "assets/js/25.3c2fe6d8.js",
    "revision": "0f3fdefd015c7ce29773332694c1bdf9"
  },
  {
    "url": "assets/js/26.28526ee4.js",
    "revision": "6d7482f1fd744d4cbdd5aa5fba7b93ba"
  },
  {
    "url": "assets/js/27.b6610f56.js",
    "revision": "b692fcc119f454b4a125b612350f3601"
  },
  {
    "url": "assets/js/28.9e9493f7.js",
    "revision": "af74d2730625ad725447fb6a3132ada0"
  },
  {
    "url": "assets/js/29.175ae6d2.js",
    "revision": "26414e8c0b8fbfb81f3a5868bd5edbd0"
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
    "url": "assets/js/5.c8637072.js",
    "revision": "5cfdf306ca7f5c4940f1f70ba8d953a6"
  },
  {
    "url": "assets/js/6.00be2eba.js",
    "revision": "6be76da2134b0c4e15d882c65da07237"
  },
  {
    "url": "assets/js/7.047683d6.js",
    "revision": "ff1dc5603b3c11fbaf1ab8ad5164889a"
  },
  {
    "url": "assets/js/8.0ab8ad07.js",
    "revision": "356a40e949c1b2bad9f7484a22598bdf"
  },
  {
    "url": "assets/js/9.37ef6b17.js",
    "revision": "f1e0894131cc729d1ab73ce0a842b788"
  },
  {
    "url": "assets/js/app.2ede4e21.js",
    "revision": "769f0eb320eb653b92e143cb8a2fae5e"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "61381cc119330a9db1f3ea0c60b64c87"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "8f5281088f8835de1ad3b4e91acddc24"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "e83154eed38d7f28e389625f4e1d0ed2"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "7bb0664377b85bb31492f0b9522c68a0"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "9972e26725af9084ea613962305954fe"
  },
  {
    "url": "en-us/Download.html",
    "revision": "b6a779a61a3dedde7b4e8911490ae2b9"
  },
  {
    "url": "en-us/index.html",
    "revision": "07432b58184d2ddc535f4f4dacd65e6d"
  },
  {
    "url": "en-us/Support.html",
    "revision": "220295cf800aea8d9236712aa49f9d5e"
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
    "revision": "23b363708439a45891c31f235d519d11"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "69d8fe8d39cb18efc4811a9594ad84e4"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "0c9dd00dc21e110301283d571ae74953"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "624ed1f27ac8181d3486d77125726ee7"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "5794b2654d336888c58c6cf515235b5e"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "cb6c78e0860e193e5d162e0a078dfcb6"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "dbb06a356f3f60c21062ab75cad67a17"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "22a7ef32693e5e3b37060339ecc3b403"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "5066dd7496890b146e8e9f9a52563285"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "9bd937b862353adae58cc8260f7b107e"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "d742f8806c24bd132eabd7542d136796"
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
