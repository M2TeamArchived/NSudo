module.exports = {
  head: [
    ['link', { rel: 'shortcut icon', type: "image/x-icon", href: `/favicon.ico` }]
 ],
  base: "/NSudo/",
  dest: "../../docs",
  themeConfig: {
    repo: "M2Team/NSudo",
    docsDir: "src/Documents",
    logo: '/assets/img/logo.png', 
    editLinks: true,
    locales: {
      "/en-us/": {
        title: 'NSudo',
        description: 'NSudo - System Administration Toolkit',
        selectText: "Languages",
        label: "English",
        editLinkText: "Edit this page on GitHub",
        serviceWorker: {
          updatePopup: {
            message: "New content is available.",
            buttonText: "Refresh"
          }
        },
        lastUpdated: 'Last Updated',
        nav: require('./nav/en-us'),
        sidebar: {
          "/en-us/docs/": [
            "/en-us/docs/",
            {
              title: "Documents",
              children: [
                "/en-us/docs/Changelog",
                "/en-us/docs/DevilMode",
                "/en-us/docs/SharedLibrary",
                ["/en-us/docs/People", "Relevant People"]
              ]
            }
          ]
        }
      },
      "/zh-hans/": {
        title: 'NSudo',
        description: 'NSudo - 系統管理工具包',
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
        nav: require('./nav/zh-hans'),
        sidebar: {
          "/zh-hans/docs/": [
            "/zh-hans/docs/",
            {
              title: "档案",
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
        title: 'NSudo',
        description: 'NSudo - 系統管理工具包',
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
        nav: require('./nav/zh-hant'),
        sidebar: {
          "/zh-hant/docs/": [
            "/zh-hant/docs/",
            {
              title: "檔案",
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
  locales: {
    "/en-us/": {
      lang: "en-US",
      title: "NSudo",
      description: "System Administration Toolkit"
    },
    "/zh-hans/": {
      lang: "zh-CN",
      title: "NSudo",
      description: "系统管理工具包"
    },
    "/zh-hant/": {
      lang: "zh-TW",
      title: "NSudo",
      description: "系統管理工具包"
    }
  }
};
