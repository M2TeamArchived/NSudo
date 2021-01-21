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
    "revision": "9142efa3f5c8078545b5bdef1ee77dbf"
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
    "url": "assets/js/11.e04af4d1.js",
    "revision": "272b42150223603b89ca8457c8e310f9"
  },
  {
    "url": "assets/js/12.58db3ac4.js",
    "revision": "f2f5f0b02ac09af971c30916116aab01"
  },
  {
    "url": "assets/js/13.0a0c8d89.js",
    "revision": "6c0493e75d2cb887f8509cd6776ddc6f"
  },
  {
    "url": "assets/js/14.7c444340.js",
    "revision": "be3b4ced6305640131f6c7dcd33f3715"
  },
  {
    "url": "assets/js/15.5774c73c.js",
    "revision": "f945e7ff16ad2113539228dcaf0b16ee"
  },
  {
    "url": "assets/js/16.5290c082.js",
    "revision": "7f7a006bdaa494bdfbcac2ca1e5848df"
  },
  {
    "url": "assets/js/17.743cb56e.js",
    "revision": "b2fdf391bd2dc60e6cea15e761f65f32"
  },
  {
    "url": "assets/js/18.22aaadd7.js",
    "revision": "77622d50a5b3a610997a6ac9dfedda7e"
  },
  {
    "url": "assets/js/19.25e1dde9.js",
    "revision": "be4fad037b6f3bff9b9137a9956bf5a5"
  },
  {
    "url": "assets/js/2.070eee7d.js",
    "revision": "bd3c547fabc31436d7f2e7f9b757e67d"
  },
  {
    "url": "assets/js/20.75173979.js",
    "revision": "eae55d952a9b8f1d1bb689643a2737fc"
  },
  {
    "url": "assets/js/21.108206fe.js",
    "revision": "490edfbf8ca12ae1ebd16fc3a7f861b5"
  },
  {
    "url": "assets/js/22.292e3234.js",
    "revision": "b6cbeea32ff255176b580729249bf787"
  },
  {
    "url": "assets/js/23.f64a55e7.js",
    "revision": "558f2a6733c82bd196d2eefd99b7582a"
  },
  {
    "url": "assets/js/24.9c53b4d9.js",
    "revision": "05ed9c6fea7b4db3d9afdf04fc8f9d25"
  },
  {
    "url": "assets/js/25.9334d54f.js",
    "revision": "360780f751afeb13228d1460c56624e7"
  },
  {
    "url": "assets/js/26.f59e5f33.js",
    "revision": "eac9c17b58b88ba210bcf5022a88e7c7"
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
    "url": "assets/js/7.58bcd016.js",
    "revision": "0c4f1bee5ce795601d071ad6bbaceb5f"
  },
  {
    "url": "assets/js/8.40e1c603.js",
    "revision": "d29b3f1b336a5019b31677f0177b3468"
  },
  {
    "url": "assets/js/9.c430fcf0.js",
    "revision": "e8217c04ffe5108394d203d024ea3db3"
  },
  {
    "url": "assets/js/app.6f178a1b.js",
    "revision": "bc3da4d46776c91da3fd083473a9c82a"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "b088038d3ad154aac52c75024474c9a1"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "c198ab92b49eba77f413c2985d69a713"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "3e7e575c9e1141edc3dc19742647fe3c"
  },
  {
    "url": "en-us/docs/People.html",
    "revision": "5fc013b210a7bd15890a512b31e1dbe3"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "06b92fb3f50a405290f6d67d23afffd7"
  },
  {
    "url": "en-us/Download.html",
    "revision": "aaab2568a19f8992531ec27ff86c70d3"
  },
  {
    "url": "en-us/index.html",
    "revision": "a8cc43b84cf1ed374eab81bf2fca8130"
  },
  {
    "url": "en-us/Support.html",
    "revision": "3958cd0879da47194c04ad944c79066f"
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
    "revision": "0978d3635612e553c71dc3a22be043b7"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "2f547163ea4d984b1611a9d52b316e5d"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "3732220b3b95799fc20267f21152ee95"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "c9838293aef13b0a42a956ecc1aaf2f6"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "f623680cae19b6205a8cdc40a464e097"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "5ede99f21feb870322b174ad7991d950"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "511cee159acd7901175c253dd1ee92d5"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "f1efbb4678986401cd6ab0525c2d7843"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "5b8e6e83920bc46c6df8a0c171d1c64a"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "e5ae66b6c052f99dd024126af5896851"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "e4474924891d95e587c46ddff3c99c44"
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
