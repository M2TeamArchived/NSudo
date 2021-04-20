module.exports = {
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
  },
	footer: [
		{
			text: "Copyright &copy; <a href='https://m2team.org/' target='_blank'>M2-Team</a> and Contributors. All rights reserved. "
		},
		{
			text: "<a href='https://github.com/M2Team/NSudo/blob/master/License.md' target='_blank'>MIT</a> Licensed"
		},
		{
			text: " GitHub Issue ",
			link: "https://github.com/M2Team/NSudo/issues"
		}
	]
}