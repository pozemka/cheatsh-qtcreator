# CheatSh-QtCreator
Plug-in for QtCreator to view cheat sheets from [cheat.sh](https://github.com/chubin/cheat.sh)

[Download here](https://github.com/pozemka/cheatsh-qtcreator/releases)

## Introduction
[Cheat.sh](https://github.com/chubin/cheat.sh) is a community-driven cheat sheets repository for programming languages, databases, linux tools and commands. It is also searches StackOverflow if no answer was found in repository. This plugin provides integrated access to cheat.sh from Qt Creator.

For example you want to know how to get random number in a range. Instead of switching to documentaion or to browser you can search with plug-in for `random in range` and read cheat sheet right inside Qt Creator.

Search examples:
<a href="http://cheat.sh/cpp/tie" target="_blank">tie</a>,
<a href="http://cheat.sh/cpp/RAII" target="_blank">RAII</a>,
<a href="http://cheat.sh/cpp/random+in+range" target="_blank">random in range</a>,
<a href="http://cheat.sh/cpp/measure+time" target="_blank">measure time</a>,
<a href="http://cheat.sh/cpp/reverse+a+list" target="_blank">reverse a list</a>.
<a href="http://cheat.sh/QML/js+function" target="_blank">QML/js function</a>,
<a href="http://cheat.sh/Qt/resources" target="_blank">Qt/resources</a>,
<a href="http://cheat.sh/SQL/select" target="_blank">SQL/select</a>,
<a href="http://cheat.sh/tar" target="_blank">tar</a>

## Usage
### From editor
Right-click on a word or selection and choose `Search cheat.sh`
from popup menu. Or hit <kbd>Alt</kbd> + <kbd>⇧ Shift</kbd> + <kbd>c</kbd>

<details><summary>Context menu example animation</summary>

![Context menu example animation](https://raw.githubusercontent.com/pozemka/resources/master/contextmenu.gif)

</details>

### From Locator
1. Hit <kbd>Ctrl</kbd> + <kbd>k</kbd> to focus Locator
2. Type `cs <search term>` to search in default context or `cs /<context>/<search term>` to override context for this search

<details><summary>Locator menu example animation</summary>
  
![Locator example animation](https://raw.githubusercontent.com/pozemka/resources/master/locator.gif)

</details>

### Useful settings
Plugin setting allows you to:
* change default search context to your favorite language (default value is C++ language)
* set custom URL to self-hosted cheat.sh instance
* turn on and off displaying comments in results
* disable update checks

## Installation
To install plug-in, please download suitable version from [releases page](https://github.com/pozemka/cheatsh-qtcreator/releases). 
Then extract plugin to user plug-ins directory which is:
* `"%LOCALAPPDATA%\QtProject\qtcreator\plugins"` on Windows Vista and later (For example `c:\Users\Username\AppData\Local\QtProject\QtCreator\plugins`)
* `"~/.local/share/data/QtProject/qtcreator/plugins"` or `"$XDG_DATA_HOME/data/QtProject/qtcreator/plugins"` on Linux

Please note:
* for Qt Creator **prior 4.9.0** plug-in must be put into subdirectory with exact match to Qt Creator version (For example `…/QtProject/qtcreator/plugins/4.8.2`). Starting **from 4.9.0** you can put plug-in into subdirectory with lowest patch version (e.g. 4.9.0 instead of 4.9.2).
* Qt Creator **4.9.x for Windows** has broken SSL support so you should [install OpenSSL manually](https://github.com/pozemka/cheatsh-qtcreator/wiki/OpenSSL).

## Compilation
See [INSTALL](INSTALL.md) for more info about compilation from sources.

## TODO:
* quick paste of results
