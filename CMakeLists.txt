cmake_minimum_required(VERSION 3.10)

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

include_directories(ANSIEsc2HTML/src)
add_subdirectory(ANSIEsc2HTML)

# Qt5LinguistTools
find_package(Qt5LinguistTools)
set(TS_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/i18n/cheatsh_ru.ts
)
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION
${CMAKE_CURRENT_BINARY_DIR}/i18n)
#file(GLOB_RECURSE TS_SOURCES "*.cpp" "*.h" "*.ui")
#qt_create_translation(QM_FILES ${TS_FILES} ${TS_SOURCES})
qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/i18n ${TS_FILES})

exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}/.git
  ARGS "--work-tree" "${CMAKE_CURRENT_SOURCE_DIR}" "describe" "--always" "--tags" "--abbrev=0"
  OUTPUT_VARIABLE GIT_VERSION )

add_definitions( -DGIT_VERSION="${GIT_VERSION}")

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
    ${QM_FILES}
    resources.qrc
    i18n/i18n.qrc
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
