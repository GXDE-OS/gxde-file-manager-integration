# GXDE 文件管理器集成插件

## 项目简介
GXDE 文件管理器集成插件项目为GXDE桌面环境提供扩展功能，包含以下核心插件：
1. 网页浏览插件 - 支持在文件管理器中直接浏览网页
2. 剪贴板文件查看插件 - 可查看系统剪贴板中的文件内容
3. Nutstore同步状态标记插件 - 显示文件的Nutstore同步状态

## 主要功能
- **剪贴板文件监控**
  实现DClipboardFileWatcher类监控剪贴板变化，支持获取剪贴板文件列表和状态监控

- **文件信息扩展**
  提供DClipboardFileInfo类扩展文件信息显示，支持自定义列显示和权限管理

- **插件架构支持**
  通过DFMFileControllerPlugin接口实现插件化架构，支持动态加载和卸载功能模块

## 核心组件
- **clipboard-files** - 剪贴板文件处理模块
- **nutstore-dfm-plugin** - Nutstore同步状态显示模块
- **webview** - 网页浏览模块
- **thumbnail** - 缩略图生成模块（字体文件处理）

## 开发环境
基于Qt框架开发，使用QMake构建系统，支持跨平台编译。项目采用DFM（Deepin File Manager）插件架构，可无缝集成到GXDE桌面环境。

## 许可协议
本项目采用开源许可协议，请参见debian/copyright文件获取完整许可信息。