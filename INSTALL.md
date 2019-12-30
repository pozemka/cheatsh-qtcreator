In progress...

## Windows
1. [Build Qt Creator from sources](https://wiki.qt.io/Building_Qt_Creator_from_Git)
2. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
3. `cd cheatsh-qtcreator`
4. qmake "IDE_SOURCE_TREE=<Path to Qt Creator sources>" "IDE_BUILD_TREE=<Path to Qt Creator build>" cheatsh.pro
    For example: 
    `d:\projects\cheatsh-qtcreator>qmake "IDE_SOURCE_TREE=d:\projects\3rdparties\qt-creator-opensource-src-4.11.0" "IDE_BUILD
_TREE=d:\projects\3rdparties\qt-creator-4.11.0-x64-build" cheatsh.pro`
5. nmake release