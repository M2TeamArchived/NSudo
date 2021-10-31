# ![Logo](Logo.png) NSudo - Инструментарий системного администрирования

[![AppVeyor CI](https://ci.appveyor.com/api/projects/status/github/M2Team/NSudo?branch=master&svg=true)](https://ci.appveyor.com/project/MouriNaruto/nsudo)
[![Latest Version](https://img.shields.io/github/release/M2Team/NSudo.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Latest Release Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/latest/total.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Total Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/total.svg)](https://github.com/M2Team/NSudo/releases)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](License.md)
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FM2Team%2FNSudo.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FM2Team%2FNSudo?ref=badge_shield)

[简体中文](Readme.zh-CN.md) | [English](Readme.md)

Это репозиторий исходного кода NSudo. Если вы хотите посетить официальный сайт NSudo, 
скачать NSudo или прочитать документацию по NSudo и т.д., пожалуйста, посетите страницу
https://nsudo.m2team.org.

Этот файл readme будет документом, ориентированным на разработчиков, поскольку он 
находится в репозитории исходного кода.

## Дорожная карта развития на 2021 год

- [x] Добавить режим текущего пользователя (повышенный).
  - [x] Реализовать общую библиотеку NSudo.
  - [x] Реализовать NSudo Launcher.
- [ ] Использование wxWidgets для реализации пользовательского интерфейса.
- [ ] Конфигурационный файл среды на основе TOML.
- [ ] Добавить больше API в общую библиотеку NSudo.
- [ ] Экспорт PDF непосредственно с официального сайта.
- [x] Улучшить работу зеркала Gitee.
  - [x] Перевести readme в корне дерева источника.
  - [x] Автоматическая синхронизация при коммите.

## Благодарности

Пожалуйста, прочтите [People.md](People.md).

## Правила поведения

Пожалуйста, прочтите [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## Внесение вклада в NSudo

### Как стать участником внесения вклада

- Прямые вклады
  - **Создавайте pull request'ы напрямую.**
  - Если у вас есть вопросы, пожалуйста, пишите на Mouri_Naruto@Outlook.com.
- Обратная связь о предложениях и ошибках.
  - Мы используем GitHub issues для отслеживания ошибок и предложений.
  - Для устранения ошибок и общих вопросов, пожалуйста, 
    [создайте новый вопрос](https://github.com/M2Team/NSudo/issues/new).

### Руководство по внесению написанию кода

#### Prerequisites

- Visual Studio 2017 Version 15.9 or later.
  - You also need install ARM64 components (MSVC Toolchain and ATL/MFC) if you
    want to compile ARM64 version of NSudo.
- Windows 10 Version 1507 SDK or later.
  - You also need install ARM64 components when you installing the Windows 10
    Version 1703 SDK or later and you want to compile ARM64 version of NSudo.

#### Как создать все целевые объекты NSudo

Запустите `BuildAllTargets.bat` в `Source/Native`.

#### Как изменить или отладить NSudo

Откройте `NSudo.sln` в `Source/Native`.

#### Стиль кода и соглашения

- C++: [Основные рекомендации C++](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- C#: Следуйте стилю команды .NET Core [стиль кода C#](https://github.com/dotnet/corefx/blob/master/Documentation/coding-guidelines/coding-style.md)

Для всех языков соблюдайте файл [.editorconfig](https://editorconfig.org/), 
указанный в дереве исходного текста. Многие IDE поддерживают эту возможность 
изначально или с помощью плагина.

#### Копирование файлов из других проектов

Следующие правила должны соблюдаться для Pull request'ов, включающих файлы из другого 
проекта:
- Лицензия файла является
  [пермиссивной](https://ru.wikipedia.org/wiki/Разрешительная_лицензия_свободного_ПО).
- Лицензия файла остаётся нетронутой.
- При необходимости вклад правильно атрибутируется в файле [лицензии](License.md)
  в репозитории.

### Способ обновления документации.

Обратите внимание сюда https://github.com/M2Team/NSudo/pull/29.

Для создания новых документов вам потребуется установить [Node.js](https://nodejs.org) и 
[Yarn](https://yarnpkg.com) в вашей системе и запустить `build.bat` в
`Website`.

Движок документации основан на [VuePress](https://v1.vuepress.vuejs.org).
