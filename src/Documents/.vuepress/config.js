module.exports = {
  base: "/NSudo/",
  dest: "../../docs",
  temp: ".temp",
  cache: ".cache",
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
  themeConfig: {
    repo: 'm2team/NSudo',
    editLinks: true,
    docsDir: 'src/Documents',
    logo: '/assets/img/logo.png',
    lastUpdated: true,
    locales: {
      "/en-us/": {
        selectText: "Languages",
        label: "English",
        editLinkText: "Edit this page on GitHub",
        serviceWorker: {
          updatePopup: { message: "New content is available.", buttonText: "Refresh" }
        },
        lastUpdated: 'Last Updated',
        nav: [
          { text: "Home", link: "/en-us/" },
          { text: "Download", link: "/en-us/Download" },
          { text: "Support", link: "/en-us/Support" },
          { text: "Documents", link: "/en-us/docs/" }
        ],
        sidebar: {
          "/en-us/docs/": [
            "/en-us/docs/",
            {
              title: "Documents",
              collapsable: false,
              children: [
                "/en-us/docs/Changelog",
                "/en-us/docs/DevilMode",
                "/en-us/docs/SharedLibrary",
                ["/en-us/docs/People", "Relevant People"]
              ]
            }
          ]
        },
      },
      "/zh-hans/": {
        selectText: "选择语言",
        label: "简体中文",
        editLinkText: "在 GitHub 上编辑此页",
        serviceWorker: {
          updatePopup: {
            message: "发现新内容可用。",
            buttonText: "刷新"
          }
        },
        lastUpdated: '最后更新时间',
        nav: [
          { text: "首页", link: "/zh-hans/" },
          { text: "下载", link: "/zh-hans/Download" },
          { text: "支持", link: "/zh-hans/Support" },
          { text: "文档", link: "/zh-hans/docs/" }
        ],
        sidebar: {
          "/zh-hans/docs/": [
            "/zh-hans/docs/",
            {
              title: "档案",
              collapsable: false,
              children: [
                ["/zh-hans/docs/Changelog", "更新日志"],
                ["/zh-hans/docs/DevilMode", "NSudo 恶魔模式"],
                ["/en-us/docs/People", "相关人士"]
              ]
            }
          ]
        }
      },
      "/zh-hant/": {
        selectText: "選擇語言",
        label: "繁體中文",
        editLinkText: "在 GitHub 上編輯此頁",
        serviceWorker: {
          updatePopup: {
            message: "發現新內容可用。",
            buttonText: "重載"
          }
        },
        lastUpdated: '最後更新時間',
        nav: [
          { text: "主頁", link: "/zh-hant/" },
          { text: "下載", link: "/zh-hant/Download" },
          { text: "支援", link: "/zh-hant/Support" },
          { text: "文獻", link: "/zh-hant/docs/" }
        ],
        sidebar: {
          "/zh-hant/docs/": [
            "/zh-hant/docs/",
            {
              title: "檔案",
              collapsable: false,
              children: [
                ["/zh-hant/docs/Changelog", "變更紀錄"],
                ["/en-us/docs/People", "相關人士"]
              ]
            }
          ]
        }
      }
    }
  },
  plugins: [
    '@vuepress/back-to-top',
    '@vuepress/medium-zoom',
    '@vuepress/pwa', {
      serviceWorker: true,
      updatePopup: true
    }
  ]
}