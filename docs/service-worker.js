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
    "revision": "3b9aed631a0b0f7a3e116e059354986a"
  },
  {
    "url": "assets/css/0.styles.3628aaca.css",
    "revision": "a97fbc8289ff7627e074f3d911007dd2"
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
    "url": "assets/js/10.9af8fd87.js",
    "revision": "0afe890ac40c303b37f6b7df58f033c3"
  },
  {
    "url": "assets/js/11.12a87181.js",
    "revision": "9b331d5fc154231323fb8e70dc0e42d6"
  },
  {
    "url": "assets/js/12.2c84fb6d.js",
    "revision": "c16ebae0d4534b47f49a1202652d8613"
  },
  {
    "url": "assets/js/13.822c4061.js",
    "revision": "4c9500f989931ceff4c50f092fbac24d"
  },
  {
    "url": "assets/js/14.490c3a7d.js",
    "revision": "3868e5ca993410031721480a4b2d2e79"
  },
  {
    "url": "assets/js/15.b1d122e0.js",
    "revision": "30ed98e0cec89733633d96af491f6273"
  },
  {
    "url": "assets/js/16.bf077ad5.js",
    "revision": "b00942dda9ace951f7467a6d5b6a10c4"
  },
  {
    "url": "assets/js/17.7c4f1410.js",
    "revision": "98dad2172fb9f11fb9139b6debf4ea82"
  },
  {
    "url": "assets/js/18.50a656b5.js",
    "revision": "c06fe2678fe1f4e380fb97a9201fc78c"
  },
  {
    "url": "assets/js/19.e620135b.js",
    "revision": "870eebcddf14cfd32e3fda4a89b605f2"
  },
  {
    "url": "assets/js/2.4b587f60.js",
    "revision": "b8477b7346594ab5e4e866fa776f3ff0"
  },
  {
    "url": "assets/js/20.533ce6b4.js",
    "revision": "55e0907cec9ec035d3dce59f8a253a50"
  },
  {
    "url": "assets/js/21.b59e4d4e.js",
    "revision": "f32e2bca462b9dae1f95f33ab7b577f9"
  },
  {
    "url": "assets/js/22.2b27c738.js",
    "revision": "868eb86bc0570953919cfdfd550e9b80"
  },
  {
    "url": "assets/js/23.f069c36d.js",
    "revision": "0469f940f38e12e0b67e9eeb801d4600"
  },
  {
    "url": "assets/js/24.7cc0d21b.js",
    "revision": "cd3fea6158187c970ebcf2e5f74173a7"
  },
  {
    "url": "assets/js/25.698c623e.js",
    "revision": "79335b85a5383c4f57f285fa78856397"
  },
  {
    "url": "assets/js/26.e2ac13f2.js",
    "revision": "2a0d7373365443c956f334d43faaae8a"
  },
  {
    "url": "assets/js/27.cb46c919.js",
    "revision": "e4d1a4666ac6fd3497a7a4cfa58a2e8b"
  },
  {
    "url": "assets/js/28.b6843826.js",
    "revision": "766596ce7b3f59520f240af6717a4221"
  },
  {
    "url": "assets/js/3.73d7b621.js",
    "revision": "ed06cd22636f3e6626706974d79fd322"
  },
  {
    "url": "assets/js/4.61df5732.js",
    "revision": "5964e5f04eba8832b800c2c6aed3c4e2"
  },
  {
    "url": "assets/js/5.bd375cb0.js",
    "revision": "a536e9023ccb181a5266575d7f04e2d7"
  },
  {
    "url": "assets/js/6.5ecb1414.js",
    "revision": "61bd9cf9b9b6623dbdfe9d0f4035af08"
  },
  {
    "url": "assets/js/7.3c18824d.js",
    "revision": "278f7903274cf41b8825f7da1a9f51ed"
  },
  {
    "url": "assets/js/8.15d5bd47.js",
    "revision": "e8c5bf3dd2342b4d7af776ec525045b4"
  },
  {
    "url": "assets/js/9.a3ddf7ad.js",
    "revision": "9d80ffaf6842546c1175272b03bf98e5"
  },
  {
    "url": "assets/js/app.21f1c68a.js",
    "revision": "bfa2cc8e8283dfbf8659afcffc088b1b"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "8f0ca7cd1efad5cf35e15c3cbe18a5f6"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "0eb1d926eb11b81660adec9945facbb0"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "d834dc4b50e58a210f0805dda7403e51"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "fa4d67064bfccbfb44bba5c937db8255"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "58ed2ebcd45c23b7ffcc789d076be8d4"
  },
  {
    "url": "en-us/Download.html",
    "revision": "898e1ed4854e4aae1e7b181a19d3b37b"
  },
  {
    "url": "en-us/index.html",
    "revision": "00c554382723118e7219d1ab988bae03"
  },
  {
    "url": "en-us/Support.html",
    "revision": "2086f644043bed2e5bbdbbaa784c762c"
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
    "revision": "2cd390845548f4e3abd54c4d9edade1a"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "f79c5d460188975278ad584294c76b25"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "84d9fa00a25795f90264925deffab97d"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "6afbcdc05efee162fc05c584fd1ac939"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "3e788ac5fbdbbe0a58ff48a71a426af9"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "bde5b5118e6f7dbc34581c13e9ce6c23"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "c5ad21ba89b20f25a52ae76edf2ee0d7"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "122cce550209275400792d9c361a4433"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "c9a379ed36fb03882fc34365065fcb60"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "c45aa62e3a7d91bca10587cb94e708e1"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "a473a792805bacd258cb32a99bd187d5"
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
