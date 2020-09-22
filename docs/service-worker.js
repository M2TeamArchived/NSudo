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
    "revision": "49a8f16bee18ff5dfb72267cccdd5cb7"
  },
  {
    "url": "assets/css/0.styles.6387d49d.css",
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
    "url": "assets/js/10.dab89e9e.js",
    "revision": "0afe890ac40c303b37f6b7df58f033c3"
  },
  {
    "url": "assets/js/11.85619008.js",
    "revision": "9b331d5fc154231323fb8e70dc0e42d6"
  },
  {
    "url": "assets/js/12.53a7986b.js",
    "revision": "d5421f64d4da1c7578652ea487d5c414"
  },
  {
    "url": "assets/js/13.7f476582.js",
    "revision": "af626bc3376acca2d9993f192ad45192"
  },
  {
    "url": "assets/js/14.7b610171.js",
    "revision": "3868e5ca993410031721480a4b2d2e79"
  },
  {
    "url": "assets/js/15.7b530195.js",
    "revision": "30ed98e0cec89733633d96af491f6273"
  },
  {
    "url": "assets/js/16.aefafbe2.js",
    "revision": "0b12b70aae90ed34275e673a345d4917"
  },
  {
    "url": "assets/js/17.6fe03b44.js",
    "revision": "6c87f13f8ef20d23a80b07447e54375a"
  },
  {
    "url": "assets/js/18.b41f99ae.js",
    "revision": "efa763d10562d697b28f164c23ee48bb"
  },
  {
    "url": "assets/js/19.5d7e62f4.js",
    "revision": "d7f93bf0200a8fd0a8591d32da7929e6"
  },
  {
    "url": "assets/js/2.1ea12864.js",
    "revision": "f4f9390aa6ddf9f1ba85845d67b6bde6"
  },
  {
    "url": "assets/js/20.f67e1d2a.js",
    "revision": "c02911ec04c821dbfdeeffab7416f5ad"
  },
  {
    "url": "assets/js/21.2345f1e6.js",
    "revision": "e29ba7058960f992de152fc2945ec40e"
  },
  {
    "url": "assets/js/22.38ab5293.js",
    "revision": "71994124dfcd35b52c0f5166f47fc05e"
  },
  {
    "url": "assets/js/23.bf9223e2.js",
    "revision": "93be3e8e744900b4b4053fa2f2bd0477"
  },
  {
    "url": "assets/js/24.505c7028.js",
    "revision": "29805e052dbecab56128c933a983df01"
  },
  {
    "url": "assets/js/25.537b6073.js",
    "revision": "d98161b021048214a70143d4063f085c"
  },
  {
    "url": "assets/js/26.b2dae6bb.js",
    "revision": "2a0d7373365443c956f334d43faaae8a"
  },
  {
    "url": "assets/js/27.04f48497.js",
    "revision": "e4d1a4666ac6fd3497a7a4cfa58a2e8b"
  },
  {
    "url": "assets/js/28.b450a16c.js",
    "revision": "766596ce7b3f59520f240af6717a4221"
  },
  {
    "url": "assets/js/3.0cf2345f.js",
    "revision": "c648bed152066bdb95c81911fd3b9dd1"
  },
  {
    "url": "assets/js/4.a88ed73e.js",
    "revision": "5964e5f04eba8832b800c2c6aed3c4e2"
  },
  {
    "url": "assets/js/5.837c212b.js",
    "revision": "eba6454dd90058b117c26cb85f4c87d2"
  },
  {
    "url": "assets/js/6.b69ed7d4.js",
    "revision": "60a0f19463da816a4f2539e4766797a6"
  },
  {
    "url": "assets/js/7.3801417b.js",
    "revision": "24a728b3e76842eaf23ce1644484f3f9"
  },
  {
    "url": "assets/js/8.06edb4cb.js",
    "revision": "e8c5bf3dd2342b4d7af776ec525045b4"
  },
  {
    "url": "assets/js/9.326352f9.js",
    "revision": "9d80ffaf6842546c1175272b03bf98e5"
  },
  {
    "url": "assets/js/app.26715022.js",
    "revision": "80e484d17d9cdd7c6f7f5dc58508d545"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "2490e289ce9f1d839dd2c26c39cead0b"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "3a1f27d86a0eea46b45d322e4b347f5f"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "c83928fcadb6ca7c61b74b59ff845468"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "8920a3f27e52ed9622aecb7c143c030d"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "82a6a0f4a3d6290b6161ab7db6be0fde"
  },
  {
    "url": "en-us/Download.html",
    "revision": "6887a13ed433ceb0ffcacdfea1d6da6b"
  },
  {
    "url": "en-us/index.html",
    "revision": "17577dba025df5236ea678b3a2ecdf09"
  },
  {
    "url": "en-us/Support.html",
    "revision": "1a1b491057cd2fb2c5eb565f14be4d52"
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
    "revision": "da53b24d6e6d9cd2fe4a6a3da970fca6"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "3053e1a68da38df05952028cee414d26"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "dd62e7ed24d3ba5d27649815380c8ed5"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "3c7c5893015d12118342e987ba1815aa"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "98ab98ab2f99a4a330f6812a02ab5eb1"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "3b1f318bc9cfe9117588529b02334131"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "43db5d59bf130c4e73bd8ebcbaff454d"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "50db6bc686d296526bdeebb06cc5d02c"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "c234c8df279315f62ae5372f07cafb56"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "53737a196f48cc76a9a67a3bd8e0b8ed"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "4bb7a82c6c051e4fa87561573917b99e"
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
