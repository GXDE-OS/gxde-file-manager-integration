QT       += core gui

TEMPLATE = lib
CONFIG += plugin link_pkgconfig
PKGCONFIG += gxde-file-manager

DESTDIR = $$_PRO_FILE_PWD_/../controllers

OTHER_FILES += clipboard-files.json

target.path = /usr/lib/$${QMAKE_HOST.arch}-linux-gnu/gxde-file-manager/plugins/controllers

INSTALLS += target

SOURCES += \
    main.cpp \
    dclipboardfilecontroller.cpp \
    dclipboardfileinfo.cpp

HEADERS += \
    dclipboardfilecontroller.h \
    dclipboardfileinfo.h
