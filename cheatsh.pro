DEFINES += CHEATSH_LIBRARY

QT += network

# CheatSh files

SOURCES += \
    cheatshplugin.cpp \
    cheatoutputplane.cpp \
    cheatfilter.cpp \
    optionspage.cpp \
    querymanager.cpp \
    settings.cpp \
    optionsdialog.cpp \
    updatechecker.cpp

HEADERS += \
    cheatshplugin.h \
    cheatsh_global.h \
    cheatshconstants.h \
    cheatoutputplane.h \
    cheatfilter.h \
    optionspage.h \
    querymanager.h \
    settings.h \
    optionsdialog.h \
    updatechecker.h

FORMS += \
    optionsdialog.ui

TRANSLATIONS += \
    i18n/cheatsh_ru.ts

OTHER_FILES += \
    CheatSh.json.in \
    README.md \
    INSTALL.md


INCLUDEPATH += $$PWD/ANSIEsc2HTML/src

LIBS += -L$$PWD/ANSIEsc2HTML/build -lANSIEsc2HTML_static

# Automatic ANSIEsc2HTML build

unix {
MAKE_BIN = make
SPLIT = ;
}
win32 {
MAKE_BIN = nmake
SPLIT = &
}

CONFIG(debug, debug|release) {  # release
    QMAKE_CONFIG = "CONFIG+=debug"
} else {    # debug
    QMAKE_CONFIG = "CONFIG+=release"
}
message($$QMAKE_CONFIG)

ansiesc2htmllib.target = ANSIEsc2HTML
ansiesc2htmllib.depends = FORCE
ansiesc2htmllib.commands = echo "Building ANSIEsc2HTML..." $$SPLIT \
                           cd $$PWD/ANSIEsc2HTML $$SPLIT \
                           $$QMAKE_QMAKE $$QMAKE_CONFIG $$SPLIT \
                           $$MAKE_BIN $$SPLIT \
                           echo "Done building ANSIEsc2HTML."
PRE_TARGETDEPS += ANSIEsc2HTML #compiler_lrelease_make_all
QMAKE_EXTRA_TARGETS += ansiesc2htmllib

win32 {
CONFIG += lrelease embed_translations  # doesn't work on Linux. https://stackoverflow.com/a/53872260/149897
RESOURCES += \
    cheatsh_win32.qrc
}
unix {
RESOURCES += \
    cheatsh_unix.qrc
    QMAKE_EXTRA_COMPILERS += lrelease  # doesn't work on Windows. kek
    lrelease.nmae          = LRELEASE compiler
    lrelease.input         = TRANSLATIONS
    lrelease.output        = ${QMAKE_FILE_BASE}.qm
    lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm $$PWD/i18n/${QMAKE_FILE_BASE}.qm
    lrelease.CONFIG       += no_link target_predeps
}

extraclean.commands = cd $$PWD/ANSIEsc2HTML $$SPLIT \
                          $$MAKE_BIN clean
clean.depends += extraclean

extradistclean.commands = cd $$PWD/ANSIEsc2HTML $$SPLIT \
                          $$MAKE_BIN distclean
distclean.depends += extradistclean

QMAKE_EXTRA_TARGETS += extraclean clean extradistclean distclean

# Automatic versioning
GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags --abbrev=0)
message($$GIT_VERSION)
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"


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

### There is a trick to fool Qt Creator's dependencies check on Windows. First comment QTC_PLUGIN_DEPENDS and try to build until it fails to link. Then uncomment QTC_PLUGIN_DEPENDS. Run qmake and nmake again. It will produce dll compatible with wider variety of Qt Creator versions. It is may be a bad idea still.
QTC_PLUGIN_DEPENDS += \
    coreplugin \
    texteditor

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)
