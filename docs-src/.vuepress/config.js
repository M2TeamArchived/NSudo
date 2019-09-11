module.exports = {
  base: "/NSudo/",
  dest: "../docs",
  themeConfig: {
    repo: "M2Team/NSudo",
    docsDir: "docs-src",
    editLinks: true,
    locales: {
      "/": {
        selectText: "Languages",
        label: "English",
        editLinkText: "Edit this page on GitHub",
        serviceWorker: {
          updatePopup: {
            message: "New content is available.",
            buttonText: "Refresh"
          }
        },
        nav: [
          { text: "Home", link: "/" },
          {
            text: 'Downloads',
            items: [
              { text: 'Current Release', link: 'https://github.com/M2Team/NSudo/releases/latest' },
              { text: 'All Releases', link: 'https://github.com/M2Team/NSudo/releases' },
              { text: 'AppVeyor CI', link: 'https://ci.appveyor.com/project/MouriNaruto/nsudo' },
              { text: 'Git Repository Mirror - Gitee', link: 'https://gitee.com/M2-Team/NSudo' }
            ]
          },
          { text: "Docs", link: "/docs/" },
          {
            text: 'Communities',
            items: [
              { text: 'GitHub', link: 'https://github.com/M2Team/NSudo/issues' },
              { text: 'My Digital Life', link: 'https://forums.mydigitallife.net/threads/59268' },
              { text: 'QQ Group 466078631', link: 'https://shang.qq.com/wpa/qunwpa?idkey=ac879ff5e88f85115597a9ec5f3dbbf28a6b84d7352e2fe03b7cbacf58bb6d53'}
            ]
          },
          {
            text: "Contact",
            items: [
              { text: 'E-mail', link: 'mailto:Mouri_Naruto@Outlook.com' }
            ]
          }
        ],
        sidebar: {
          "/docs/": [
            "/docs/",
            {
              title: "Documents",
              children: [
                "/docs/Changelog",
                ["/docs/People", "Relevant People"]
              ]
            }
          ]
        }
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
        nav: [
          { text: "首页", link: "/zh-hans/" },
          {
            text: '下载',
            items: [
              { text: '当前版本', link: 'https://github.com/M2Team/NSudo/releases/latest' },
              { text: '所有版本', link: 'https://github.com/M2Team/NSudo/releases' },
              { text: 'AppVeyor CI', link: 'https://ci.appveyor.com/project/MouriNaruto/nsudo' },
              { text: 'Git 镜像仓库 - 码云', link: 'https://gitee.com/M2-Team/NSudo' }
            ]
          },
          { text: "文档", link: "/zh-hans/docs/" },
          {
            text: '社区',
            items: [
              { text: 'GitHub', link: 'https://github.com/M2Team/NSudo/issues' },
              { text: 'My Digital Life', link: 'https://forums.mydigitallife.net/threads/59268' },
              { text: 'QQ 群 466078631', link: 'https://shang.qq.com/wpa/qunwpa?idkey=ac879ff5e88f85115597a9ec5f3dbbf28a6b84d7352e2fe03b7cbacf58bb6d53' }
            ]
          },
          {
            text: "联系方式",
            items: [
              { text: '邮箱', link: 'mailto:Mouri_Naruto@Outlook.com' }
            ]
          }
        ],
        sidebar: {
          "/zh-hans/docs/": [
            "/zh-hans/docs/",
            {
              title: "档案",
              children: [
                ["/zh-hans/docs/Changelog", "更新日志"],
                ["/docs/People", "相关人士"]
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
        nav: [
          { text: "主頁", link: "/zh-hant/" },
          {
            text: '下載',
            items: [
              { text: '當前版本', link: 'https://github.com/M2Team/NSudo/releases/latest' },
              { text: '所有版本', link: 'https://github.com/M2Team/NSudo/releases' },
              { text: 'AppVeyor CI', link: 'https://ci.appveyor.com/project/MouriNaruto/nsudo' },
              { text: 'Git 鏡像倉庫 - 碼雲', link: 'https://gitee.com/M2-Team/NSudo' }
            ]
          },
          { text: "文獻", link: "/zh-hant/docs/" },
          {
            text: '社區',
            items: [
              { text: 'GitHub', link: 'https://github.com/M2Team/NSudo/issues' },
              { text: 'My Digital Life', link: 'https://forums.mydigitallife.net/threads/59268' },
              { text: 'QQ 群組 466078631', link: 'https://shang.qq.com/wpa/qunwpa?idkey=ac879ff5e88f85115597a9ec5f3dbbf28a6b84d7352e2fe03b7cbacf58bb6d53' }
            ]
          },
          {
            text: "聯繫方式",
            items: [
              { text: '電郵', link: 'mailto:Mouri_Naruto@Outlook.com' }
            ]
          }
        ],
        sidebar: {
          "/zh-hant/docs/": [
            "/zh-hant/docs/",
            {
              title: "檔案",
              children: [
                ["/zh-hant/docs/Changelog", "變更紀錄"],
                ["/docs/People", "相關人士"]
              ]
            }
          ]
        }
      }
    }
  },
  locales: {
    "/": {
      lang: "en-US",
      title: "NSudo",
      description: "A Powerful System Administration Tool"
    },
    "/zh-hans/": {
      lang: "zh-CN",
      title: "NSudo",
      description: "一个强大的系统管理工具"
    },
    "/zh-hant/": {
      lang: "zh-TW",
      title: "NSudo",
      description: "一個強大的系統管理工具"
    }
  }
};
