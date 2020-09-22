module.exports = {
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
        { text: "首页", link: "/zh-hans/", icon: 'fa fa-home' },
        { text: "下载", link: "/zh-hans/Download", icon: 'fa fa-download' },
        { text: "支持", link: "/zh-hans/Support", icon: 'fa fa-bell' },
        { text: "文档", link: "/zh-hans/docs/", icon: 'fa fa-book' }
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
}