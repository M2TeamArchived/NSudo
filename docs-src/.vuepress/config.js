module.exports = {
  themeConfig: {
    base: "/NSudo/",
    dest: "../docs",
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
        nav: [{ text: "Home", link: "/" }, { text: "Docs", link: "/docs/" }],
        sidebar: {
          "/docs/": [
            "/docs/",
            {
              title: "Documents",
              path: "/docs/",
              children: [
                "/docs/changelog",
                "/docs/People",
                "/docs/CODE_OF_CONDUCT",
                "/docs/CONTRIBUTING"
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
          { text: "文档", link: "/zh-hans/docs/" }
        ],
        sidebar: {
          "/zh-hans/docs/": [
            /* ... */
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
          { text: "文獻", link: "/zh-hant/docs/" }
        ],
        sidebar: {
          "/zh-hant/docs/": [
            /* ... */
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
