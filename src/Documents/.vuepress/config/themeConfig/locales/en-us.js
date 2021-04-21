module.exports = {
  selectText: "Languages",
  label: "English",
  editLinkText: "Edit this page on GitHub",
  serviceWorker: {
    updatePopup: { message: "New content is available.", buttonText: "Refresh" }
  },
  lastUpdated: 'Last Updated',
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