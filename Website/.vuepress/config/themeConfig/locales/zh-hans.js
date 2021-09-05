module.exports = {
  selectText: "选择语言",
  label: "简体中文",
  editLinkText: "在 GitHub 上编辑此页",
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
          ["/zh-hans/docs/SharedLibrary", "NSudo 共享库"]
        ]
      }
    ]
  },
  footer: {
    actor: 'M2-Team',
    actorLink: 'https://m2team.org/',
    licensedLink: 'https://github.com/M2Team/NSudo/blob/master/License.md',
    licensed: 'MIT',
    copyright: [
      {
        text: "GitHub Issue ",
        link: "https://github.com/M2Team/NSudo/issues"
      },
      {
        text: "相关人士",
        link: "https://github.com/M2Team/NSudo/blob/master/People.md"
      }
    ]
  }
}
