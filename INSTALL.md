## How to Build (TLDR)

`git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`

Create a build directory and run

    cmake -DCMAKE_PREFIX_PATH=<path_to_qtcreator> -DCMAKE_BUILD_TYPE=Release <path_to_plugin_source>
    cmake --build .

where `<path_to_qtcreator>` is the relative or absolute path to a Qt Creator build directory, or to a
combined binary and development package (Windows / Linux), or to the `Qt Creator.app/Contents/Resources/`
directory of a combined binary and development package (macOS), and `<path_to_plugin_source>` is the
relative or absolute path to this plugin directory.

For example:
    
    mkdir build 
    cd build 
    cmake -DCMAKE_PREFIX_PATH=/opt/slow/build/qt-creator-5.0.0 -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .


# Manual build

1. [openSUSE](#openSUSE)
3. [Arch (Manjaro)](#arch-manjaro)
4. [Windows](#Windows)

## openSUSE
and other Linux systems

Tested on openSUSE Tumbleweed

### Requirements
1. Qt Creator sources. I've got mine from Qt Creator Installer. Don't forget to check "Qt Creator Plugin Development" during installation.

### Build process
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `mkdir build`
4. `cd build`
5. `cmake -DCMAKE_PREFIX_PATH=<path_to_qtcreator_build> -DCMAKE_BUILD_TYPE=Release ..`
6. `make`

### Installation
* `sudo make install` — if you want to install system-wide.
* For user installation copy file from `lib/qtcreator/plugins/libCheatSh.so` to plugins directory (`~/.local/share/data/QtProject/qtcreator/plugins/<qt-creator-version>`). Where `<qt-creator-version>` is a lowest patch version of qt-creator. E.g. directory should be `5.0.0` for `5.0.1` version.


## Arch (Manjaro)
Not provided for now. 

If you are able to build plugin for Arch or Manjaro please provide the instructions.

## Windows
### Requirements
0. Don't forget to use same architecture everywhere. See your Qt Creator's about dialog if in doubt.
1. [Download and install OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html) (light installer is sufficient). You can choose to copy OpenSSl DLLs to the Windows system directory or to add them to the PATH environment variable manually. Read [this page](https://github.com/pozemka/cheatsh-qtcreator/wiki/OpenSSL) on wiki for more information.
2. Install Qt Creator with "Qt Creator 4.x.x Plugin Development" component selected. **NOTE:** It seems that newer versions of Qt Creator installs are missing some files needed to build plugins. In that case only way I found was to build from sources.
    * **Or** [Build Qt Creator from sources](https://github.com/qt-creator/qt-creator/blob/master/README.md#compiling-qt-creator)

### Build process
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake "IDE_SOURCE_TREE=<Path to Qt Creator>\dev" "IDE_BUILD_TREE=<Path to Qt Creator>\dev"`

    For example:
    
    `qmake "IDE_SOURCE_TREE=c:\Qt\qtcreator-4.12.0\dev" "IDE_BUILD_TREE=c:\Qt\qtcreator-4.12.0\dev"`
    * **Or** in case you built Qt Creator:
      `qmake "IDE_SOURCE_TREE=<Path to Qt Creator sources>" "IDE_BUILD_TREE=<Path to Qt Creator build>" cheatsh.pro`

      For example:
    
      `qmake "IDE_SOURCE_TREE=d:\projects\3rdparties\qt-creator-opensource-src-4.11.0" "IDE_BUILD_TREE=d:\projects\3rdparties\qt-creator-4.11.0-x64-build" cheatsh.pro`
4. `nmake release` — this installs to user plugin directory
