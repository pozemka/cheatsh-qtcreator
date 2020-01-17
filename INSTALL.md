# Manual build

1. [openSUSE](#openSUSE)
2. [Ubuntu (Kubuntu)](#ubuntu-kubuntu)
3. [Windows](#Windows)

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
3. `qmake-qt5 && make` — this installs to user's plug-in directory
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
    
4. `make` — this installs to user's plug-in directory
5. `sudo make install` — if you want to install system-wide

## Windows
### Requirements
0. Don't forget to use same architecture everywhere. See your Qt Creator's about dialog if in doubt.
1. [Download and install OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html) (light installer is sufficient). You can choose to copy OpenSSl DLLs to the Windows system directory or to add them to the PATH environment variable manually. Read [this page](https://github.com/pozemka/cheatsh-qtcreator/wiki/OpenSSL) on wiki for more information.
2. Qt Creator sources

### Build process
1. [Build Qt Creator from sources](https://wiki.qt.io/Building_Qt_Creator_from_Git)
2. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
3. `cd cheatsh-qtcreator`
4. `qmake "IDE_SOURCE_TREE=<Path to Qt Creator sources>" "IDE_BUILD_TREE=<Path to Qt Creator build>" cheatsh.pro`

    For example:
    
    `d:\projects\cheatsh-qtcreator>qmake "IDE_SOURCE_TREE=d:\projects\3rdparties\qt-creator-opensource-src-4.11.0" "IDE_BUILD
_TREE=d:\projects\3rdparties\qt-creator-4.11.0-x64-build" cheatsh.pro`
5. `nmake release` — this installs to user's plug-in directory
