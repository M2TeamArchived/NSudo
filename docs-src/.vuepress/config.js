module.exports = {
  base: "/NSudo/",
  dest: "../docs",
  themeConfig: {
    repo: "M2Team/NSudo",
    docsDir: "docs-src",
    editLinks: true,
    locales: {
      "/en-us/": {
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
          { text: "下载", link: "/zh-hans/Download" },
          { text: "支持", link: "/zh-hans/Support" },
          { text: "文档", link: "/zh-hans/docs/" }
        ],
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
          { text: "下載", link: "/zh-hant/Download" },
          { text: "支援", link: "/zh-hant/Support" },
          { text: "文獻", link: "/zh-hant/docs/" }
        ],
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
