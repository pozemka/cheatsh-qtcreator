In progress...

## Windows
### Requirements
0. Don't forget to use same architecture everywhere. See your Qt Creator's about dialog if in doubt.
1. Download and install OpenSSL for Windows. 
1. * [download OpenSSL installer](https://slproweb.com/products/Win32OpenSSL.html). Light one is sufficient. You can chose copy OpenSSl DLLs to the Windows system directory or add them to the PATH environment variable manually.
1. * Or you can install it with via Qt online installer (see Developer and Designer Tools section). Please note that Qt installer doesn't set up OpenSSL environment. So you should add the directory with the DLLs (someting like C:\Qt\Tools\OpenSSL\Win_x64\bin) to the PATH environment variable. (see https://stackoverflow.com/a/59072649/149897)
2. Qt Creator sources

### Build process
1. [Build Qt Creator from sources](https://wiki.qt.io/Building_Qt_Creator_from_Git)
2. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
3. `cd cheatsh-qtcreator`
4. `qmake "IDE_SOURCE_TREE=<Path to Qt Creator sources>" "IDE_BUILD_TREE=<Path to Qt Creator build>" cheatsh.pro`
    For example: 
    `d:\projects\cheatsh-qtcreator>qmake "IDE_SOURCE_TREE=d:\projects\3rdparties\qt-creator-opensource-src-4.11.0" "IDE_BUILD
_TREE=d:\projects\3rdparties\qt-creator-4.11.0-x64-build" cheatsh.pro`
5. `nmake release` — this will install to user's plugin directory