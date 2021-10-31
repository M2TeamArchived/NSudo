module.exports = {
  selectText: "Языки",
  label: "Русский",
  editLinkText: "Изменить эту страницу на GitHub",
  lastUpdated: 'Последнее изменение',
  nav: [
    { text: "Главная страница", link: "/ru-ru/" },
    { text: "Скачать", link: "/ru-ru/Download" },
    { text: "Поддержка", link: "/ru-ru/Support" },
    { text: "Документация", link: "/ru-ru/docs/" }
  ],
  sidebar: {
    "/ru-ru/docs/": [
      "/ru-ru/docs/",
      {
        title: "Документация",
        collapsable: false,
        children: [
          ["/ru-ru/docs/Changelog", "Обновления"],
          ["/ru-ru/docs/DevilMode", "Режим без ограничений NSudo"],
          ["/ru-ru/docs/SharedLibrary", "Общая библиотека NSudo"]
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
        text: "Благодарности",
        link: "https://github.com/M2Team/NSudo/blob/master/People.md"
      }
    ]
  }
}
