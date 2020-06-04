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
    "revision": "91df1be8f52fc3b53949764775a3c7b3"
  },
  {
    "url": "assets/css/0.styles.32a262de.css",
    "revision": "e46e242af2c04dfd39e2c203b00641cc"
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
    "url": "assets/js/10.71490cfb.js",
    "revision": "61841805db6a59f30dbdb1f56f5cc32d"
  },
  {
    "url": "assets/js/11.45ceb117.js",
    "revision": "60701278075c6e70e5a33fbf7bc4c9fd"
  },
  {
    "url": "assets/js/12.91b70c3a.js",
    "revision": "97b4c20603e3063956507d089efba673"
  },
  {
    "url": "assets/js/13.fe738a60.js",
    "revision": "cbe9ba4e16f45bb2715ceadf32500a44"
  },
  {
    "url": "assets/js/14.44c3bd42.js",
    "revision": "bdc601c7b5efc8eda060e7a943ab55bf"
  },
  {
    "url": "assets/js/15.0d7f3a0a.js",
    "revision": "620df61539320aaa4658c74c139c4bd7"
  },
  {
    "url": "assets/js/16.d0307d5c.js",
    "revision": "cc0caca6775291140c2b975a6a3f976e"
  },
  {
    "url": "assets/js/17.963e5ffb.js",
    "revision": "a6a16d881e2cf2d352cdd878d0839757"
  },
  {
    "url": "assets/js/18.6436a75a.js",
    "revision": "25a01e9d791b4adf00aaf72babd8581b"
  },
  {
    "url": "assets/js/19.f30ce3f3.js",
    "revision": "ed16deaad32c4b67f1d440561b25b9fb"
  },
  {
    "url": "assets/js/2.d5a834a5.js",
    "revision": "3040e53694cd24f358cd380a2bd774d0"
  },
  {
    "url": "assets/js/20.c1a19119.js",
    "revision": "8c8c9940c2b0372a9d2306292f38b223"
  },
  {
    "url": "assets/js/21.fda23b85.js",
    "revision": "2ff5645c45c7d569b778607e7628bd86"
  },
  {
    "url": "assets/js/22.d7ab7d6c.js",
    "revision": "b65688e7c6e5c0013f3ad0d72a2c096a"
  },
  {
    "url": "assets/js/23.4d360a3d.js",
    "revision": "269d6787c9819bd47cac9664730119e4"
  },
  {
    "url": "assets/js/24.f17ba5bf.js",
    "revision": "966dd98caf1d80751d45c8e46c5ebc78"
  },
  {
    "url": "assets/js/25.9612fdd4.js",
    "revision": "ed54f57ba9ec5fc1115f08aeb5ac07d8"
  },
  {
    "url": "assets/js/26.1a17f96a.js",
    "revision": "5826ec6445a94a66c5c4ab294cd396ee"
  },
  {
    "url": "assets/js/27.9af8047e.js",
    "revision": "cd8c6a8e088d8c00c656524b040df22b"
  },
  {
    "url": "assets/js/28.64289fd1.js",
    "revision": "85c8f1d1de91668e6428cfa4dbff112a"
  },
  {
    "url": "assets/js/29.cbd2e8d7.js",
    "revision": "29903798966495cac4fce0624a610aea"
  },
  {
    "url": "assets/js/3.ad07f05d.js",
    "revision": "ade58ba05e0efb60b7d3efd939411067"
  },
  {
    "url": "assets/js/4.f02b07f5.js",
    "revision": "c8806b49cd3b4952bfb9a1d85b927066"
  },
  {
    "url": "assets/js/5.e02da9c1.js",
    "revision": "f514deba777b669ea9afa0d2b88504a6"
  },
  {
    "url": "assets/js/6.5b619c97.js",
    "revision": "58d0d5b48634f055f5e56b1d6de7b92c"
  },
  {
    "url": "assets/js/7.530ad1f4.js",
    "revision": "624d7b9ade23cffc8bef7ffb87a5ecfb"
  },
  {
    "url": "assets/js/8.d00e64ec.js",
    "revision": "55795e3f69fbbcc293d31efe1ce83204"
  },
  {
    "url": "assets/js/9.6e56622d.js",
    "revision": "ae6bfe5c061618748c20902667c1e4de"
  },
  {
    "url": "assets/js/app.04107a1e.js",
    "revision": "e9faa9f42b45610b226f8f6289eaac81"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "01ebab9a6a7c2e633b5702266866900f"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "9579e9563fbbbec1ab45aab9273028c3"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "55c6700c03e09e0c51e4ce1028773ee3"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "0821b0c240f0e052bfca8ce93c29a6f9"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "a1feae97bc7c430bfbcb59235d30df6a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "12073be6be7bc57fd5aa720915b32a2b"
  },
  {
    "url": "en-us/index.html",
    "revision": "ae6172c0471242fd44056eb5e6ecaffc"
  },
  {
    "url": "en-us/Support.html",
    "revision": "d213e15d8a7c6ca0d473ec0a73d4e19b"
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
    "revision": "d4366e4a671698f450440de7d89dc218"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "73896ea8c89d02fba7de5e45b3aecbf4"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "58cc0631be8fecf8b100918bf84d262e"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "8e2208841b7d06309684091c07f08baa"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "1b417c9454707f5eeda84e4e312cdfbf"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "afd0ce4f5ab2bd33b213e9c6e704bc9c"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "4a45509810360b481f07915a105735a4"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "0b8b674203c4b3104ce91b4e6ba09f47"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "a7466124ef49667784a7aa09ac5d6b3c"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "493c35449de5608f7ca438ac6a9d3e84"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "3a49910febebea3847dae5e5edda3b55"
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
