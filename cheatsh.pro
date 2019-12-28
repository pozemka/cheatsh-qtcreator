DEFINES += CHEATSH_LIBRARY

QT += network
QT += webenginewidgets

# CheatSh files

SOURCES += \
    cheatshplugin.cpp \
    cheatoutputplane.cpp \
    cheatfilter.cpp \
    optionspage.cpp \
    settings.cpp \
    optionsdialog.cpp \
    cheatsh.cpp

HEADERS += \
    cheatshplugin.h \
    cheatsh_global.h \
    cheatshconstants.h \
    cheatoutputplane.h \
    cheatfilter.h \
    optionspage.h \
    settings.h \
    optionsdialog.h \
    cheatsh.h

# Automatic ANSIEsc2HTML build
QMAKE_BIN = $$system(which qmake-qt5)

isEmpty(QMAKE_BIN) {
    QMAKE_BIN = $$system(which qmake-qt5)
    isEmpty(QMAKE_BIN) {
        message("Neither qmake or qmake-qt5 not found!")
    }
}
message($$QMAKE_BIN)

ansiesc2htmllib.target = ANSIEsc2HTML
ansiesc2htmllib.depends = FORCE
ansiesc2htmllib.commands = echo "Building ANSIEsc2HTML..."; \
                           cd $$PWD/ANSIEsc2HTML; $$QMAKE_BIN; make; \
                           echo "Done building ANSIEsc2HTML.";
PRE_TARGETDEPS += ANSIEsc2HTML
QMAKE_EXTRA_TARGETS += ansiesc2htmllib


# Qt Creator linking

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = CheatSh
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin \
    texteditor

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)

FORMS += \
    optionsdialog.ui

RESOURCES += \
    cheatsh.qrc

TRANSLATIONS += \
    i18n/cheatsh_ru.ts


INCLUDEPATH += $$PWD/ANSIEsc2HTML/src

LIBS += -L$$PWD/ANSIEsc2HTML/build -lANSIEsc2HTML_static

#CONFIG += lrelease embed_translations  // doesn't work. https://stackoverflow.com/a/53872260/149897

QMAKE_EXTRA_COMPILERS += lrelease
lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm $$PWD/i18n/${QMAKE_FILE_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
