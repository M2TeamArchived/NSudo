# Краткое руководство по плагину Mouri Optimization Plugin

## Применимая версия

- 9.0.2676.0

## MoDefragMemory

### Особенность

Выполнение дефрагментации памяти путём замены большей части содержимого из
физической памяти в страничный файл.

### Использование

> NSudoPluginHost MoPlugin.dll MoDefragMemory

## MoEnableMicrosoftUpdate

### Особенность

Включение опции "Получать обновления для других продуктов Microsoft при обновлении Windows"
в Центре обновления Windows.

### Использование

> NSudoPluginHost MoPlugin.dll MoEnableMicrosoftUpdate

## MoLaunchAppX

### Особенность

Launch an AppX application.

### Использование

> NSudoPluginHost MoPlugin.dll MoLaunchAppX [ApplicationUserModelID] [Arguments]

## MoManageCompactOS

### Особенность

Управление функцией CompactOS.

### Использование

- `/Query` Запросить состояние CompactOS.
  > NSudoPluginHost MoPlugin.dll MoManageCompactOS /Query
- `/Enable` Включить CompactOS.
  > NSudoPluginHost MoPlugin.dll MoManageCompactOS /Enable
- `/Disable` Отключить CompactOS.
  > NSudoPluginHost MoPlugin.dll MoManageCompactOS /Disable

## MoPurgeChromiumCache

### Особенность

Удаление веб-кэша в приложениях на базе Chromium, включая Chrome, Edge на
базе Chromium, приложения на базе Electron и т.д.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeChromiumCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeChromiumCache /Purge

## MoPurgeCorruptedAppXPackages

### Особенность

Удаление повреждённых пакетов AppX.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeCorruptedAppXPackages /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeCorruptedAppXPackages /Purge

## MoPurgeDeliveryOptimizationCache

### Особенность

Очистка кэша в Оптимизации доставки.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeDeliveryOptimizationCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeDeliveryOptimizationCache /Purge

## MoPurgeGeckoCache

### Особенность

Очистка веб-кэша в приложениях на основе Gecko, включая Firefox,
Waterfox, Pale Moon и др.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeGeckoCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeGeckoCache /Purge

## MoPurgeNuGetCache

### Особенность

Очистка кэша в NuGet безопасно.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeNuGetCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeNuGetCache /Purge

## MoPurgePackageCache

### Особенность

Безопасная очистка кэша в папке Package Cache.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgePackageCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgePackageCache /Purge

## MoPurgeSystemRestorePoint

### Особенность

Очистка точки восстановления системы.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeSystemRestorePoint /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeSystemRestorePoint /Purge

## MoPurgeTridentCache

### Особенность

Очистка веб-кэша в приложениях на базе Trident, включая Internet Explorer,
Legacy Edge, приложения на базе MSHTML, приложения на базе
Edge WebView и т.д.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeTridentCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeTridentCache /Purge

## MoPurgeVisualStudioCodeCache

### Особенность

Очистка кэша в Visual Studio Code.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioCodeCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioCodeCache /Purge

## MoPurgeVisualStudioInstallerCache

### Особенность

Безопасная очистка кэша в установщике Visual Studio.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioInstallerCache /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioInstallerCache /Purge

## MoPurgeWindowsEventLog

### Особенность

Очистка Журнала событий Windows.

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsEventLog /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsEventLog /Purge

## MoPurgeWindowsSetup

### Особенность

Очистка Установщика Windows, включая предыдущую установку (установки) Windows,
временные файлы установки Windows, файлы, удалённые при обновлении Windows,
файлы установки Windows ESD и файлы журнала обновления Windows. 

### Использование

- `/Scan` Сканировать этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsSetup /Scan
- `/Purge` Удалить этот элемент.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsSetup /Purge

## MoUpdateAppXPackages

### Особенность

Обновление приложения из Microsoft Store.

### Использование

- Ничего.
  > NSudoPluginHost MoPlugin.dll MoUpdateAppXPackages
- `/Loop` Зациклить операцию до тех пор, пока ни один пакет не будет нуждаться в обновлении.
  > NSudoPluginHost MoPlugin.dll MoUpdateAppXPackages /Loop
