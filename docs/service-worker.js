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
    "revision": "979ad65f38dd028db2767d737c328819"
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
    "url": "assets/js/13.aa604d5e.js",
    "revision": "eddf2ad4f51cb4b344e5a9dcbd0aa40d"
  },
  {
    "url": "assets/js/14.d309f47a.js",
    "revision": "6e84d8e3a649a6067dc750a24d1bfe36"
  },
  {
    "url": "assets/js/15.7a087cac.js",
    "revision": "8440b3b1133b954655fe1673be4849d0"
  },
  {
    "url": "assets/js/16.0bead983.js",
    "revision": "0461dea6a5bbae799c05cc2a91d40407"
  },
  {
    "url": "assets/js/17.64a5b797.js",
    "revision": "abee3b02f5a39359f73e9a2e126f6e57"
  },
  {
    "url": "assets/js/18.3c351b29.js",
    "revision": "d5e785748bfc222ce0881c5b66c522aa"
  },
  {
    "url": "assets/js/19.3bed64a4.js",
    "revision": "e20bc6664f5388ab5441eda30419d171"
  },
  {
    "url": "assets/js/2.e8602ec3.js",
    "revision": "bcf9ed510aea7a5402280461c097cc8f"
  },
  {
    "url": "assets/js/20.0c3c7d34.js",
    "revision": "fd643d6c0e9db06a7e37ccc66d7a4ab7"
  },
  {
    "url": "assets/js/21.eee2ab4d.js",
    "revision": "24221c984c9485cf83be48d18c4ae717"
  },
  {
    "url": "assets/js/22.1fcbb8c4.js",
    "revision": "5b5e0186130d48eadf26c101441bc59d"
  },
  {
    "url": "assets/js/23.31ae9a91.js",
    "revision": "37652b3d129b8edca8885de18d7e56d8"
  },
  {
    "url": "assets/js/24.4e1d4a51.js",
    "revision": "5c68ac365c6db1ff42e683ba3ebb79a8"
  },
  {
    "url": "assets/js/25.79e5dc4f.js",
    "revision": "924e96c47ba3a534f145040d3272b758"
  },
  {
    "url": "assets/js/26.ded9cb95.js",
    "revision": "235540d712c6f63196d7c4d1e8779b2a"
  },
  {
    "url": "assets/js/3.18944315.js",
    "revision": "f92ec2b16b47ac516779bd7847fb39bf"
  },
  {
    "url": "assets/js/4.1cb4f3aa.js",
    "revision": "f7f137ff0940545fb5dddf606881f4d4"
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
    "url": "assets/js/8.f29ace6a.js",
    "revision": "420991fd79bb1aa2b1b723de40a214b9"
  },
  {
    "url": "assets/js/9.6c6164c1.js",
    "revision": "4246de8cd0ddaac267d7e625a4e60098"
  },
  {
    "url": "assets/js/app.ddfdf9d0.js",
    "revision": "4c729579e12f98b01b380b6237765298"
  },
  {
    "url": "en-us/docs/Changelog.html",
    "revision": "24bc4642cb1e934a11e22a3d66e28a0f"
  },
  {
    "url": "en-us/docs/DevilMode.html",
    "revision": "00063a505844e3281fbabfb8fb6bc121"
  },
  {
    "url": "en-us/docs/index.html",
    "revision": "f605c251b1fdb532fac1575454341f84"
  },
  {
    "url": "en-us/docs/SharedLibrary.html",
    "revision": "9e97b2ba81e966e41813210b26db9f9a"
  },
  {
    "url": "en-us/Download.html",
    "revision": "d1dacf568602cd0b5497f71a19644140"
  },
  {
    "url": "en-us/index.html",
    "revision": "db0644687772b5599eb6269a7b06bf4d"
  },
  {
    "url": "en-us/Support.html",
    "revision": "dbeacb8009a54c8f52804fc15619e26b"
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
    "revision": "f3d0af60fadb4b6bdbc2bac10f39fdda"
  },
  {
    "url": "zh-hans/docs/DevilMode.html",
    "revision": "c62224323bc992c536c36daf7f98e54b"
  },
  {
    "url": "zh-hans/docs/index.html",
    "revision": "2ac9d97b2172e67436083159df8ab036"
  },
  {
    "url": "zh-hans/Download.html",
    "revision": "9923c71041034e648339fcd85a8833b5"
  },
  {
    "url": "zh-hans/index.html",
    "revision": "c0af03e5f5f8c9904deae1fa319acd14"
  },
  {
    "url": "zh-hans/Support.html",
    "revision": "5cd4422b0c3469ab900b510db83c71b3"
  },
  {
    "url": "zh-hant/docs/Changelog.html",
    "revision": "c1cf0073a8d03a2f25c6d34b87a5054f"
  },
  {
    "url": "zh-hant/docs/index.html",
    "revision": "c81fac9b01995af84c356add16f09dfe"
  },
  {
    "url": "zh-hant/Download.html",
    "revision": "233b59fb49f2b95c2a2d32963bbd23d6"
  },
  {
    "url": "zh-hant/index.html",
    "revision": "49079684c748aca6796600c116f12d41"
  },
  {
    "url": "zh-hant/Support.html",
    "revision": "bbdb1105f755ce5c07a8c8eb909949d9"
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
