# CheatSh-QtCreator
Plugin for QtCreator to view cheat sheets from [cheat.sh](https://github.com/chubin/cheat.sh)

[Download here](https://github.com/pozemka/cheatsh-qtcreator/releases)

## Usage
### From editor
Select some text or just put text cursor on the word. Right click word or selection and choose `Search cheat.sh` from menu. Or hit <kbd>Alt</kbd> + <kbd>⇧ Shift</kbd> + <kbd>c</kbd>

<details><summary>Context menu example animation</summary>

![Context menu example animation](https://raw.githubusercontent.com/pozemka/resources/master/contextmenu.gif)

</details>

### From Locator
1. Hit <kbd>Ctrl</kbd> + <kbd>k</kbd> to focus Locator
2. Type `cs <search term>` to search in default context or `cs /<context>/<search term>` to override context for this search

<details><summary>Locator menu example animation</summary>
  
![Locator example animation](https://raw.githubusercontent.com/pozemka/resources/master/locator.gif)

</details>

## Installation:
To install plugin please download suitable version from [releases page](https://github.com/pozemka/cheatsh-qtcreator/releases). 
Then extract plugin to user plugins directory which is:
* `"%LOCALAPPDATA%\QtProject\qtcreator\plugins"` on Windows Vista and later (For example `c:\Users\Username\AppData\Local\QtProject\QtCreator\plugins`)
* `"~/.local/share/data/QtProject/qtcreator/plugins"` or `"$XDG_DATA_HOME/data/QtProject/qtcreator/plugins"` on Linux

Please note that plugin must be put into subdirectory according to Qt Creator version (For example `…/QtProject/qtcreator/plugins/4.8.2`)

## Compilation
See [INSTALL](INSTALL.md) for more info about compilation from sources.

## TODO:
* quick paste of results
