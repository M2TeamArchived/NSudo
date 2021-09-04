module.exports = {
  selectText: "Languages",
  label: "English",
  editLinkText: "Edit this page on GitHub",
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
          "/en-us/docs/SharedLibrary"
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
        text: "Relevant People",
        link: "https://github.com/M2Team/NSudo/blob/master/People.md"
      }
    ]
  }
}
