module.exports = {
  base: "/NSudo/",
  dest: "../../docs",
  locales: {
    '/en-us/': {
      lang: 'en-US',
      title: 'NSudo',
      description: 'System Administration Toolkit'
    },
    '/zh-hans/': {
      lang: 'zh-CN',
      title: 'NSudo',
      description: '系统管理工具包',
    },
    '/zh-hant/': {
      lang: 'zh-TW',
      title: 'NSudo',
      description: '系統管理工具包'
    }
  },
  head: [
    ['meta', { 'http-equiv': 'X-UA-Compatible', content: "IE=edge" }],
    ['meta', { name: 'author', content: "M2-Team" }],
    ['meta', { name: 'keywords', content: 'trustedinstaller,system,session,windows,token,integritylevel,privileges,nsudo,administration,process,devilmode,bypass,accesscheck,ntapi,launcher' }],
    ['meta', { name: 'theme-color', content: '#2582D3' }],
    ['meta', { name: 'apple-mobile-web-app-capable', content: 'yes' }],
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }],
    ['meta', { name: 'msapplication-TileImage', content: '/icons/msapplication-icon-144x144.png' }],
    ['meta', { name: 'msapplication-TileColor', content: '#000000' }],
    ['meta', { name: 'Copyright', content: "Copyright M2-Team All Rights Reserved." }],
    ['link', { rel: 'icon', href: '/favicon.ico' }],
    ['link', { rel: 'manifest', href: '/manifest.json' }],
    ['link', { rel: 'apple-touch-icon', href: '/icons/apple-touch-icon-152x152.png' }],
    ['link', { rel: 'mask-icon', href: '/icons/safari-pinned-tab.svg', color: '#2582D3' }],
  ],
  theme: '@qcyblm/vpx',
  themeConfig: {
    repo: 'm2team/NSudo',
    repoicon: 'fab fa-github',
    editLinks: true,
    docsDir: 'src/Documents',
    logo: '/assets/img/logo.png',
    lastUpdated: true,
    locales: {
      "/en-us/": require('./locales/en-us'),
      "/zh-hans/": require('./locales/zh-Hans'),
      "/zh-hant/": require('./locales/zh-Hant')
    },
  },
  plugins: [
    '@vuepress/back-to-top',
    '@vuepress/medium-zoom',
    '@vuepress/pwa', {
      serviceWorker: true,
      updatePopup: true
    },
    ['vuepress-plugin-code-copy',
      {
        color: 'rgba(255,255,255,0.4)',
      }
    ],
  ]
}