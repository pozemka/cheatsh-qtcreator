1. [openSUSE](#openSUSE)
2. [Ubuntu (Kubuntu)](#ubuntu-kubuntu)
3. [Windows](#Windows)

## openSUSE
Tested on openSUSE 15.1
### Requirements
1. install `libqt5-creator-plugin-devel`
2. re-login after installation
3. link Qt Creator libraries directory to /usr/lib: 

    `sudo ln -s /usr/lib64/qtcreator /usr/lib`

### Build process
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake-qt5 && make` — this will install to user's plugin directory
4. `sudo make install` — if you want to install system-wide

## Ubuntu (Kubuntu)
Tested on Kubuntu 19.10
### Requirements
1. enable software sources either by editing `/etc/apt/sources.list` or using GUI
2. install `git`, `build-essential`, `qt5-default` and `qtcreator`
3. install Qt Creator sources using `apt source qtcreator`. This will download and extract sources into the current directory. For example:

    `user@kubuntu64-build:~/projects$ apt source qtcreator`
    
4. link Qt Creator libraries directory to /usr/lib: 

    `sudo ln -s /usr/lib/x86_64-linux-gnu/qtcreator/ /usr/lib`

### Build process
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake "IDE_SOURCE_TREE=<Path to Qt Creator sources>" "IDE_BUILD_TREE=<Path to Qt Creator build>" cheatsh.pro`
    For example:
    
    `qmake "IDE_SOURCE_TREE=/home/user/projects/qtcreator-4.8.2" "IDE_BUILD_TREE=/usr" cheatsh.pro`
    
4. `make` — this will install to user's plugin directory
5. `sudo make install` — if you want to install system-wide 

## Windows
### Requirements
0. Don't forget to use same architecture everywhere. See your Qt Creator's about dialog if in doubt.
1. Download and install OpenSSL for Windows. This is required only if you plan to use Qt Creator that you built. Installed Qt Creator is shipped with necessary libraries. As alternative you can switch to unsecure connection by changing address of server in the plugin's settings to `http://cheat.sh`. Please note that update checks are not possible without OpenSSL (GitHub redirects to https).
   * [download OpenSSL installer](https://slproweb.com/products/Win32OpenSSL.html). Light one is sufficient. You can choose to copy OpenSSl DLLs to the Windows system directory or to add them to the PATH environment variable manually.
   * Or you can install it with via Qt online installer (see Developer and Designer Tools section). Please note that Qt installer doesn't set up OpenSSL environment. So you should add the directory with the DLLs (something like `C:\Qt\Tools\OpenSSL\Win_x64\bin`) to the PATH environment variable. ([see so](https://stackoverflow.com/a/59072649/149897)). 
   * See also [OpenSSL](https://github.com/pozemka/cheatsh-qtcreator/wiki/OpenSSL)
   * See also https://doc.qt.io/QT-5/windows-requirements.html#ssl
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
