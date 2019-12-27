# CheatSh-QtCreator
Plugin for QtCreator to view cheat sheets from [cheat.sh](https://github.com/chubin/cheat.sh)

## Usage
### From editor
Select something or just put text cursor on the word. Right click word or selection and select `Search cheat.sh` from menu or hit <kbd>Meta</kbd> + <kbd>⇧ Shift</kbd> + <kbd>c</kbd>
### From Locator
1. Hit <kbd>Ctrl</kbd> + <kbd>k</kbd> to focus Locator
2. Type `cs <search term>` to search in default context or `cs \<context>\<search term>` to override context for this search

## Compilation and installation:
### Requirements
You will need Qt Creator Plugin Development Files:

* **openSUSE 15.1:** install `libqt5-creator-plugin-devel`
* * re-login after installation
* * do `sudo ln -s /usr/lib64/qtcreator /usr/lib`
* **Ubuntu** ***UNTESTED*** install `qtcreator-dev`
* Or [build Qt Creator from sources](https://wiki.qt.io/Building_Qt_Creator_from_Git). Then:
* * Either set the IDE_SOURCE_TREE when running qmake,
or set the QTC_SOURCE environment variable, to override the default setting.
* * Either set the IDE_BUILD_TREE when running qmake,
or set the QTC_BUILD environment variable, to override the default setting

### Build steps
0. `export QTC_SOURCE="/home/user/qt-creator-src"` — (optional) unpacked Qt Creator sources
0. `export  QTC_BUILD="/home/user/qtcreator-build"` — (optional) path to Qt Creator build from that sources
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake-qt5 && make` — this will install to user's plugin directory
4. `sudo make install` — if you want to install sytem-wide 

## TODO:
* quick paste of results