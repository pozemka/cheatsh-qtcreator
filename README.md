# CheatSh-QtCreator
Plugin for QtCreator to view cheat sheets from [cheat.sh](https://github.com/chubin/cheat.sh)

[Download here](github.com/pozemka/cheatsh-qtcreator/releases)

## Usage
### From editor
Select something or just put text cursor on the word. Right click word or selection and select `Search cheat.sh` from menu or hit <kbd>Meta</kbd> + <kbd>⇧ Shift</kbd> + <kbd>c</kbd>

<details><summary>Context menu example animation</summary>

![Context menu example animation](https://raw.githubusercontent.com/pozemka/resources/master/contextmenu.gif)

</details>

### From Locator
1. Hit <kbd>Ctrl</kbd> + <kbd>k</kbd> to focus Locator
2. Type `cs <search term>` to search in default context or `cs \<context>\<search term>` to override context for this search

<details><summary>Locator menu example animation</summary>
  
![Locator example animation](https://raw.githubusercontent.com/pozemka/resources/master/locator.gif)

</details>

## Compilation and installation:
See [INSTALL](INSTALL.md) for more info

0. `export QTC_SOURCE="/home/user/qt-creator-src"` — (optional) unpacked Qt Creator sources
0. `export  QTC_BUILD="/home/user/qtcreator-build"` — (optional) path to Qt Creator build from that sources
1. `git clone --recursive https://github.com/pozemka/cheatsh-qtcreator.git`
2. `cd cheatsh-qtcreator`
3. `qmake-qt5 && make` — this will install to user's plugin directory
4. `sudo make install` — if you want to install system-wide

## TODO:
* quick paste of results
