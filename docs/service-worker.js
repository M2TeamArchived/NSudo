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
    "revision": "0ca2f84869ca5a2f9e1f89d0ac88c07a"
  },
  {
    "url": "assets/css/0.styles.4c3e4e8e.css",
    "revision": "3e9864f361359a69b0009d1ba14d37ed"
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
    "url": "assets/js/10.086c5079.js",
    "revision": "60f76d472bcb22566a09678ea9b9b88a"
  },
  {
    "url": "assets/js/11.157bc1c0.js",
    "revision": "80ca47ac19b812f4be03f0bb08866814"
  },
  {
    "url": "assets/js/12.209a29f5.js",
    "revision": "e6c698e820fb79c8f34daccd24608367"
  },
  {
    "url": "assets/js/13.fc381782.js",
    "revision": "bd87fbea3929b622ab1e01ae0a5f544b"
  },
  {
    "url": "assets/js/14.7d8758af.js",
    "revision": "8ed2442c6f884055cb8bd2f4d11f7342"
  },
  {
    "url": "assets/js/15.bad00a72.js",
    "revision": "f5e96b227150409ca8eb0071974b99ee"
  },
  {
    "url": "assets/js/16.2ce21c62.js",
    "revision": "d2da7b47d1d79d00fb188b4b9e8e53bd"
  },
  {
    "url": "assets/js/17.6af8b32f.js",
    "revision": "85c2af27de10fb74cce646644723019b"
  },
  {
    "url": "assets/js/18.21fcf0f4.js",
    "revision": "94074d5ec8eee8d872a84e5e058f0c33"
  },
  {
    "url": "assets/js/19.f67ae0b7.js",
    "revision": "248ddab5f443617fa2ecba7dc9887aba"
  },
  {
    "url": "assets/js/2.e8602ec3.js",
    "revision": "bcf9ed510aea7a5402280461c097cc8f"
  },
  {
    "url": "assets/js/20.c436e33a.js",
    "revision": "2d2915ae63d2ff3ced62ed9ecd8100d1"
  },
  {
    "url": "assets/js/21.4c9332f4.js",
    "revision": "5fed9a78f4dea8ce1ff90facb33a7119"
  },
  {
    "url": "assets/js/22.0a24e693.js",
    "revision": "14c8b7be967270a5cac0bb64224387db"
  },
  {
    "url": "assets/js/23.5ac4bd66.js",
    "revision": "f69314ebb2d31711d26bac583d9b2774"
  },
  {
    "url": "assets/js/24.a97dc87e.js",
    "revision": "a667f4a071c352dd3997fbb1fdfca56b"
  },
  {
    "url": "assets/js/25.85668ed0.js",
    "revision": "909e1792dd40bef1d0f58a74f9af5e19"
  },
  {
    "url": "assets/js/26.5488dff9.js",
    "revision": "8f5c6fdee8f455036b53c149f6088307"
  },
  {
    "url": "assets/js/27.44caee2d.js",
    "revision": "b6433046633cf5c937d11e240a3fa1ad"
  },
  {
    "url": "assets/js/3.18944315.js",
    "revision": "f92ec2b16b47ac516779bd7847fb39bf"
  },
  {
    "url": "assets/js/4.6c5a58d1.js",
    "revision": "98c2cd310ee1aadf0d3aba843091deb3"
  },
  {
    "url": "assets/js/5.f19d5ce6.js",
    "revision": "4dea739bf3f57c1b44fe18631ed894c7"
  },
  {
    "url": "assets/js/6.6a96ee48.js",
    "revision": "979683756c485e0ca8ebadc3f09e89d6"
  },
  {
    "url": "assets/js/7.5fe34ec8.js",
    "revision": "e51c746df1634fb6c437f30a3b03e783"
  },
  {
    "url": "assets/js/8.03a044bc.js",
    "revision": "ef1f13c40557547830369178e6dcbef8"
  },
  {
    "url": "assets/js/9.f52909d6.js",
    "revision": "81801eb9fb57edf83cf34a6e7e7e8dfd"
  },
  {
    "url": "assets/js/app.55d669c8.js",
    "revision": "fd7fc84069a305cb5c722a0a79f7da21"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "0ae2d8fce93ba14d1be1da424c274a32"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "57f75f3cbe9e4d82d927be41ebcfc549"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "981af29c1923c1df84ec017708a824ab"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "51de1b79161266436cd58ea3c7c108f6"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "1de3e651f1e086a6c98ee56cc33e3df8"
  },
  {
    "url": "en-us/Download.html",
    "revision": "7f14971ecf39bf49e3579430be9b5562"
  },
  {
    "url": "en-us/index.html",
    "revision": "39454f8483258ead7a7e41d739968d37"
  },
  {
    "url": "en-us/Support.html",
    "revision": "c626db65807bdd997d044d9f32cd7e11"
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
    "revision": "6f79929fa594a8b8f82b90f7acb4e2ea"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "60de9b712687355f7440553a88db8e68"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "6c3317ccb500e4c59418ae018bfbdfb6"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "747ca2a178d40246f559d5ef328fef95"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "9411181e9470162f51e5883d9f23a68e"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "3af5c1800e6ae272b5cc7fbbfbd36094"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "16dbd9183d241169443e1bf17aae93cd"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "6698533938222d1bc218152e86a0941f"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "03062c4c1363224717335ce406eb4185"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "61b9002ed42c8de57c95fbc88b12e0db"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "cf584122115ae16847b699d7cbb29d7b"
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
