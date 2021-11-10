# Mouri Optimization Plugin Quickguide

## Applicable Version

- 9.0.2676.0

## MoDefragMemory

### Feature

Perform defrag for memory via swapping most contents from the physical memory
to the page file.

### Usage

> NSudoPluginHost MoPlugin.dll MoDefragMemory

## MoEnableMicrosoftUpdate

### Feature

Enable the "Receive updates for other Microsoft products when you update 
Windows" option in Windows Update.

### Usage

> NSudoPluginHost MoPlugin.dll MoEnableMicrosoftUpdate

## MoLaunchAppX

### Feature

Launch an AppX application.

### Usage

> NSudoPluginHost MoPlugin.dll MoLaunchAppX [ApplicationUserModelID] [Arguments]

## MoManageCompactOS

### Feature

Manage the CompactOS feature.

### Usage

- `/Query` Query the CompactOS state.
  > NSudoPluginHost MoPlugin.dll MoManageCompactOS /Query
- `/Enable` Enable CompactOS.
  > NSudoPluginHost MoPlugin.dll MoManageCompactOS /Enable
- `/Disable` Disable CompactOS.
  > NSudoPluginHost MoPlugin.dll MoManageCompactOS /Disable

## MoPurgeChromiumCache

### Feature

Purge the web cache in the Chromium-based applications, including Chrome, 
Chromium-based Edge, Electron-based applications, etc.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeChromiumCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeChromiumCache /Purge

## MoPurgeCorruptedAppXPackages

### Feature

Purge the corrupted AppX packages.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeCorruptedAppXPackages /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeCorruptedAppXPackages /Purge

## MoPurgeDeliveryOptimizationCache

### Feature

Purge the cache in the Delivery Optimization.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeDeliveryOptimizationCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeDeliveryOptimizationCache /Purge

## MoPurgeGeckoCache

### Feature

Purge the web cache in the Gecko-based applications, including Firefox, 
Waterfox, Pale Moon, etc.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeGeckoCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeGeckoCache /Purge

## MoPurgeNuGetCache

### Feature

Purge the cache in the NuGet safely.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeNuGetCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeNuGetCache /Purge

## MoPurgePackageCache

### Feature

Purge the cache in the Package Cache folder safely.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgePackageCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgePackageCache /Purge

## MoPurgeSystemRestorePoint

### Feature

Purge the system restore points.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeSystemRestorePoint /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeSystemRestorePoint /Purge

## MoPurgeTridentCache

### Feature

Purge the web cache in the Trident based applications, including Internet 
Explorer, Legacy Edge, MSHTML based applications, Edge WebView based 
applications, etc.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeTridentCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeTridentCache /Purge

## MoPurgeVisualStudioCodeCache

### Feature

Purge the cache in the Visual Studio Code.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioCodeCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioCodeCache /Purge

## MoPurgeVisualStudioInstallerCache

### Feature

Purge the cache in the Visual Studio Installer safely.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioInstallerCache /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioInstallerCache /Purge

## MoPurgeWindowsEventLog

### Feature

Purge the Windows Event Log.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsEventLog /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsEventLog /Purge

## MoPurgeWindowsSetup

### Feature

Purge the Windows Setup, including Previous Windows installation(s), Temporary 
Windows installation files, Files discarded by Windows upgrade, Windows ESD 
installation files and Windows upgrade log files.

### Usage

- `/Scan` Scan this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsSetup /Scan
- `/Purge` Purge this item.
  > NSudoPluginHost MoPlugin.dll MoPurgeWindowsSetup /Purge

## MoUpdateAppXPackages

### Feature

Update the apps from Microsoft Store.

### Usage

- No arguments.
  > NSudoPluginHost MoPlugin.dll MoUpdateAppXPackages
- `/Loop` Loop the operation until no packages need to upgrade.
  > NSudoPluginHost MoPlugin.dll MoUpdateAppXPackages /Loop
