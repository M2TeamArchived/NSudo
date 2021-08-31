module.exports = {
  selectText: "選擇語言",
  label: "繁體中文",
  editLinkText: "在 GitHub 上編輯此頁",
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
          ["/zh-hant/docs/DevilMode", "NSudo 惡魔模式"],
          ["/zh-hant/docs/SharedLibrary", "NSudo 共享庫"]
        ]
      }
    ]
  },
	footer: [
		{
			text: "Copyright &copy; <a href='https://m2team.org/' target='_blank'>M2-Team</a> and Contributors. All rights reserved. "
		},
		{
			text: "<a href='https://github.com/M2Team/NSudo/blob/master/License.md' target='_blank'>MIT</a> Licensed "
		},
		{
			text: "GitHub Issue ",
			link: "https://github.com/M2Team/NSudo/issues"
    },
    {
      text: "相關人士",
      link: "https://github.com/M2Team/NSudo/blob/master/People.md"
    }
	]
}
