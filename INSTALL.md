# Manual build

1. [openSUSE](#openSUSE)
2. [Ubuntu (Kubuntu)](#ubuntu-kubuntu)
3. [Arch (Manjaro)](#arch-manjaro)
4. [Windows](#Windows)

## openSUSE
Tested on openSUSE 15.1
### Requirements
1. Install `libqt5-creator-plugin-devel`
2. Re-login after installation
3. Create symlink to Qt Creator libraries directory in /usr/lib:

    `sudo ln -s /usr/lib64/qtcreator /usr/lib`

### Build process
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake-qt5 && make` — this installs to user plugin directory
4. `sudo make install` — if you want to install system-wide

## Ubuntu (Kubuntu)
Tested on Kubuntu 19.10
### Requirements
1. Enable software sources either by editing `/etc/apt/sources.list` or using GUI
2. Install `git`, `build-essential`, `qt5-default` and `qtcreator`
3. Install Qt Creator sources using `apt source qtcreator`. This will download and extract sources into the current directory. For example:

    `user@kubuntu64-build:~/projects$ apt source qtcreator`
    
4. Create symlink to Qt Creator libraries directory in /usr/lib:

    `sudo ln -s /usr/lib/x86_64-linux-gnu/qtcreator/ /usr/lib`

### Build process
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake "IDE_SOURCE_TREE=<Path to Qt Creator sources>" "IDE_BUILD_TREE=<Path to Qt Creator build>" cheatsh.pro`
    For example:
    
    `qmake "IDE_SOURCE_TREE=/home/user/projects/qtcreator-4.8.2" "IDE_BUILD_TREE=/usr" cheatsh.pro`
    
4. `make` — this installs to user plugin directory
5. `sudo make install` — if you want to install system-wide


## Arch (Manjaro)
Tested on Manjaro 19.0.2
### Requirements
1. Qt Creator sources

### Build process
1. Build Qt Creator from sources. For example source are in the `/home/user/projects/3rdparties/qt-creator-opensource-src-4.11.0`, build is in the `/home/user/projects/3rdparties/qt-creator-opensource-4.11.0-x64-build`
2. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
3. `cd cheatsh-qtcreator`
4.
```
qmake CONFIG+=release \
    KSYNTAXHIGHLIGHTING_LIB_DIR=/usr/lib \
    KSYNTAXHIGHLIGHTING_INCLUDE_DIR=/usr/include/KF5/KSyntaxHighlighting \
    IDE_SOURCE_TREE=<Path to Qt Creator sources> \
    IDE_BUILD_TREE=<Path to Qt Creator build> \
    cheatsh.pro
```
    For example:
```
qmake CONFIG+=release \
    KSYNTAXHIGHLIGHTING_LIB_DIR=/usr/lib \
    KSYNTAXHIGHLIGHTING_INCLUDE_DIR=/usr/include/KF5/KSyntaxHighlighting \
    IDE_SOURCE_TREE=/home/user/projects/3rdparties/qt-creator-opensource-src-4.11.0 \
    IDE_BUILD_TREE=/home/user/projects/3rdparties/qt-creator-opensource-4.11.0-x64-build \
    cheatsh.pro
```
5. `make` — this installs to user plugin directory

## Windows
### Requirements
0. Don't forget to use same architecture everywhere. See your Qt Creator's about dialog if in doubt.
1. [Download and install OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html) (light installer is sufficient). You can choose to copy OpenSSl DLLs to the Windows system directory or to add them to the PATH environment variable manually. Read [this page](https://github.com/pozemka/cheatsh-qtcreator/wiki/OpenSSL) on wiki for more information.
2. Install Qt Creator with "Qt Creator 4.x.x Plugin Development" component selected. **NOTE:** It seems that newer versions of Qt Creator installs are missing some files needed to build plugins. In that case only way I found was to build from sources.
    * **Or** [Build Qt Creator from sources](https://wiki.qt.io/Building_Qt_Creator_from_Git)

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
