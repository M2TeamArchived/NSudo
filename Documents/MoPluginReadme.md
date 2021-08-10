# 毛利优化插件 简易使用方法

## 适用的内部版本发行包

- NSudo_9.0_Preview1_PluginOnly_20210803_LegnaBrighost_v1.zip
- NSudo_9.0.2654.0_Preview1_StandaloneMoPlugin_LegnaBrighost.20210806.zip
- NSudo_9.0.2659.0_TechnicalPreview_StandaloneMoPlugin.zip

## 插件宿主下的使用示例

- NSudoPluginHost MoPlugin.dll MoPurgeDeliveryOptimizationCache /Scan
- NSudoPluginHost MoPlugin.dll MoPurgeDeliveryOptimizationCache /Purge
- NSudoPluginHost MoPlugin.dll MoPurgeCorruptedAppXPackages /Scan
- NSudoPluginHost MoPlugin.dll MoPurgePackageCache /Scan
- NSudoPluginHost MoPlugin.dll MoPurgePackageCache /Purge
- NSudoPluginHost MoPlugin.dll MoPurgeChromiumCache /Scan
- NSudoPluginHost MoPlugin.dll MoPurgeChromiumCache /Purge
- NSudoPluginHost MoPlugin.dll MoPurgeTridentCache /Scan
- NSudoPluginHost MoPlugin.dll MoPurgeTridentCache /Purge
- NSudoPluginHost MoPlugin.dll MoPurgeVisualStudioCodeCache /Scan
- NSudoPluginHost MoPlugin.dll MoPurgeWindowsEventLog /Scan
- NSudoPluginHost MoPlugin.dll MoPurgeWindowsEventLog /Purge
- NSudoPluginHost MoPlugin.dll MoUpdateAppXPackages

## MoDefragMemory

### 插件功能

内存碎片整理

### 插件参数

无

## MoEnableMicrosoftUpdate

### 插件功能

开启 Microsoft Update

### 插件参数

无

## MoManageCompactOS

### 插件功能

CompactOS 管理

### 插件参数

- `/Query` 查询 CompactOS 状态
- `/Enable` 启用 CompactOS
- `/Disable` 禁用 CompactOS

## MoPurgeChromiumCache

### 插件功能

Chromium 内核缓存清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeCorruptedAppXPackages

### 插件功能

损坏的 AppX 包清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeDeliveryOptimizationCache

### 插件功能

传递优化缓存清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeNuGetCache

### 插件功能

NuGet 缓存清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgePackageCache

### 插件功能

Package Cache 目录清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeSystemRestorePoint

### 插件功能

系统还原点清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeTridentCache

### 插件功能

Trident (MSHTML 和 EdgeHtml) 内核缓存清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeVisualStudioCodeCache

### 插件功能

Visual Studio Code 缓存清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeVisualStudioInstallerCache

### 插件功能

Visual Studio Installer 缓存清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoPurgeWindowsEventLog

### 插件功能

Windows 事件日志清理

### 插件参数

- `/Scan` 扫描
- `/Purge` 清理

## MoUpdateAppXPackages

### 插件功能

Windows 商店应用一键升级

### 插件参数

无
