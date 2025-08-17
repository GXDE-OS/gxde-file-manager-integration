

# GXDE File Manager Integration Plugins

## Project Overview
The GXDE File Manager Integration Plugin project provides extension capabilities for the GXDE desktop environment, including the following core plugins:
1. Web browsing plugin - Supports direct web page browsing within the file manager
2. Clipboard file viewing plugin - Allows viewing of file contents within the system clipboard

3. Nutstore synchronization status indicator plugin - Displays Nutstore synchronization status for files

## Key Features
- **Clipboard File Monitoring**
  Implements the DClipboardFileWatcher class to monitor clipboard changes, supporting clipboard file list retrieval and status monitoring

- **File Information Extension**
  Provides the DClipboardFileInfo class to extend file information display, supporting custom column display and permission management

- **Plugin Architecture Support**
  Implements plugin-based architecture through the DFMFileControllerPlugin interface, supporting dynamic loading and unloading of functional modules

## Core Components
- **clipboard-files** - Clipboard file handling module
- **nutstore-dfm-plugin** - Nutstore synchronization status display module
- **webview** - Web browsing module
- **thumbnail** - Thumbnail generation module (font file processing)

## Development Environment
Developed based on the Qt framework using the QMake build system, supporting cross-platform compilation. The project adopts the DFM (Deepin File Manager) plugin architecture, enabling seamless integration into the GXDE desktop environment.

## License
This project uses an open-source license agreement. Please refer to the debian/copyright file for complete licensing information.