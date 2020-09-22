module.exports = {
    selectText: "Languages",
    label: "English",
    editLinkText: "Edit this page on GitHub",
    serviceWorker: {
        updatePopup: { message: "New content is available.", buttonText: "Refresh" }
    },
    lastUpdated: 'Last Updated',
    nav: [
        { text: "Home", link: "/en-us/", icon: 'fa fa-home' },
        { text: "Download", link: "/en-us/Download", icon: 'fa fa-download' },
        { text: "Support", link: "/en-us/Support", icon: 'fa fa-bell' },
        { text: "Documents", link: "/en-us/docs/", icon: 'fa fa-book' }
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
}