cmake_minimum_required(VERSION 3.14)

# Remove when sharing with others.
list(APPEND CMAKE_PREFIX_PATH "/opt/slow/build/Qt/Tools/QtCreator")

project(CheatSh)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Git)
set(QtX Qt${QT_VERSION_MAJOR})

# 3rdparites
include_directories(ANSIEsc2HTML/src)
add_subdirectory(ANSIEsc2HTML)

# Translations
find_package(Qt5LinguistTools)
set(TS_FILES
    i18n/cheatsh_ru.ts
)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/i18n)
configure_file(i18n/i18n.qrc ${CMAKE_CURRENT_BINARY_DIR}/i18n COPYONLY)

set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "i18n")

if(COMMAND qt_create_translation)
    qt_add_translation(QM_FILES ${TS_FILES})
else()
    qt5_add_translation(QM_FILES ${TS_FILES})
endif()

# Versioning
exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}/.git
  ARGS "--work-tree" "${CMAKE_CURRENT_SOURCE_DIR}" "describe" "--always" "--tags" "--abbrev=0"
  OUTPUT_VARIABLE GIT_VERSION )

add_definitions( -DGIT_VERSION="${GIT_VERSION}")

# SOURCES
add_qtc_plugin(CheatSh
  PLUGIN_DEPENDS
    QtCreator::Core
    QtCreator::TextEditor
  DEPENDS
    ${QtX}::Widgets
    QtCreator::ExtensionSystem
    QtCreator::Utils
    ANSIEsc2HTML_static
  SOURCES
    .github/workflows/build_cmake.yml
    .github/workflows/README.md
    resources.qrc

    ${TS_FILES}
    ${QM_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}/i18n/i18n.qrc

    README.md
    cheatshplugin.cpp
    cheatshplugin.h

    cheatfilter.cpp
    cheatfilter.h

    cheatoutputplane.cpp
    cheatoutputplane.h

    optionsdialog.ui
    optionsdialog.cpp
    optionsdialog.h

    optionspage.cpp
    optionspage.h

    progressreport.cpp
    progressreport.h

    querymanager.cpp
    querymanager.h

    settings.cpp
    settings.h

    updatechecker.cpp
    updatechecker.h

    cheatsh_global.h
    cheatshconstants.h

  VERSION
    ${GIT_VERSION}
)
