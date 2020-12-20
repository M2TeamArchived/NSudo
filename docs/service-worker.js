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
    "revision": "40cd8337d62ae765db085540fcf54dc4"
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
    "url": "assets/js/14.28544818.js",
    "revision": "2b51991e996bc9d2c0d63b03c22158c4"
  },
  {
    "url": "assets/js/15.2c06542c.js",
    "revision": "e48e676d203f5fe16fbf0b690926bc2b"
  },
  {
    "url": "assets/js/16.bb6ff97a.js",
    "revision": "7d5b61828a1dee3827b9f5081094259f"
  },
  {
    "url": "assets/js/17.7067dd00.js",
    "revision": "f011b912ea53f39a0b874bcf320bd48d"
  },
  {
    "url": "assets/js/18.a4fc7d1a.js",
    "revision": "05ad64331fad9dedd2f4f7cc5142acad"
  },
  {
    "url": "assets/js/19.ebe95c9d.js",
    "revision": "3e5eefdccb4db12a76ab782254589037"
  },
  {
    "url": "assets/js/2.bc8bbda9.js",
    "revision": "ef50228e22a74d3542d8b4f6bf9c9003"
  },
  {
    "url": "assets/js/20.58c89b28.js",
    "revision": "960bbfcf4a480eb186473283204b70cc"
  },
  {
    "url": "assets/js/21.f9aa9494.js",
    "revision": "8a0557b9368b58322af38daf10fd3f7e"
  },
  {
    "url": "assets/js/22.69e5ca88.js",
    "revision": "a75b9ea4f386ed4b3ad03be0bae07e5f"
  },
  {
    "url": "assets/js/23.1a149b3f.js",
    "revision": "5624844587b5ce14309fc0c4e9cd9302"
  },
  {
    "url": "assets/js/24.8256e77e.js",
    "revision": "63566e20242d9ebcc689ecd03af370d0"
  },
  {
    "url": "assets/js/25.288583ad.js",
    "revision": "c406ea56855f1767b7e95326b465faba"
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
    "url": "assets/js/28.11c4726d.js",
    "revision": "04a42b8507c2ee1824222318b14955ad"
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
    "url": "assets/js/5.a19407d7.js",
    "revision": "4e3b2cef5cf1e797d153c9e6f4f67221"
  },
  {
    "url": "assets/js/6.044cb810.js",
    "revision": "48c738c427da079ff1670ee773b119a4"
  },
  {
    "url": "assets/js/7.f59305b5.js",
    "revision": "158123b6afe230e048f10cb499699468"
  },
  {
    "url": "assets/js/8.5253f521.js",
    "revision": "e60cb55f64c1b02b945e23f16c5c9433"
  },
  {
    "url": "assets/js/9.a9555f69.js",
    "revision": "15855b74d346b29c76ee8493f236eed4"
  },
  {
    "url": "assets/js/app.a172e3f2.js",
    "revision": "9a88705fc4507a1c26903dbebfe4f77d"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "2c3c348858af1b74847a764d9c803f3b"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "7932afa246ef639effc324071dedc4b4"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "fcc5c75f109006ee4ca0c7ea82168fc9"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "64b450b610a903f7a83ad4c41a5c200f"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "76e7cb183fab6a291f8ef2538048a150"
  },
  {
    "url": "en-us/Download.html",
    "revision": "1514264a6a6e98eae29dccc01749f176"
  },
  {
    "url": "en-us/index.html",
    "revision": "c0951f9e1e24eaca6bd8e5f51cf7f5be"
  },
  {
    "url": "en-us/Support.html",
    "revision": "049e86839d1ce668a52278001bec3159"
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
    "revision": "f80d2e5f2f8314315e2a693b06513dbe"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "2b128cef2498e66d43ae02f002c7553b"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "2361571c0af8335e3372dcdc67caa0f8"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "ef68cfb455093b81da3ba9b65b705870"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "84c7d06aa95fbb04e065d45c15bf43e2"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "27704c6ab69df07b3169c5b35c2b2532"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "131950cea3bea37c847b3904006cf6a4"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "326e85386f16695022682437dc7fbcab"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "08ab245a88c02544ef23497476df9646"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "bbc0777f1c71dc58b106626b1f8fd401"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "c33aa6eaeae79f83356fb3c53dd531a6"
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
