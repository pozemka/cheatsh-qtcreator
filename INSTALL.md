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
1. Qt Creator with "Qt Creator Plugin Development" component selected.

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
0. Don't forget to use same architecture everywhere. See Qt Creator's about dialog if in doubt.
1. Qt Creator with "Qt Creator Plugin Development" component selected.

### Build process
1. Open Qt command prompt

    1.1. Open Visual studio command prompt (see for "x64 Native Tools Command Prompt for VS 2019" in start menu)
    
    1.2. Launch `qtenv2.bat` (usually at c:\Qt\5.15.2\msvc2019_64\bin)
    
2. cd to your build enviroment
3. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
4. `cd cheatsh-qtcreator`
5. `mkdir build`
6. `cd build`
7. `cmake -DCMAKE_PREFIX_PATH=<path_to_qtcreator> ..`
    For example:
    `cmake -DCMAKE_PREFIX_PATH=c:\Qt\qtcreator-5.0.0 ..`
8. `cmake --build . --config Release`

### Installation
Copy .dll from `build\lib\qtcreator\plugins\Release` to to plugins directory (`C:\Users\<username>\AppData\Local\QtProject\QtCreator\plugins\<qt-creator-version>`). Where `<qt-creator-version>` is a lowest patch version of qt-creator. E.g. directory should be `5.0.0` for `5.0.1` version.
