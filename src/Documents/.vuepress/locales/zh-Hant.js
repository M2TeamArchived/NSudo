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
        { text: "主頁", link: "/zh-hant/", icon: 'fa fa-home' },
        { text: "下載", link: "/zh-hant/Download", icon: 'fa fa-download' },
        { text: "支援", link: "/zh-hant/Support", icon: 'fa fa-bell' },
        { text: "文獻", link: "/zh-hant/docs/", icon: 'fa fa-book' }
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