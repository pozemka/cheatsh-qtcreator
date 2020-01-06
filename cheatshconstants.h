#pragma once

namespace CheatSh {
namespace Constants {

const char ACTION_ID[] = "CheatSh.Action";
const char LOCATOR_ACTION_ID[] = "CheatSh.LocatorAction";
const char MENU_ID[] = "CheatSh.Menu";
const char CONTEXT_MENU_ID[]   = "CheatSh.ContextMenu";

// Settings
const char SETTINGS_GROUP[] = "CheatSh.Plugin";
const char CHT_CONTEXT[] = "Context";
const char CHT_URL[] = "URL";
const char CHT_COMMENTS[] = "commentsEnabled";
const char CHT_CHECK_UPDATES[] = "checkUpdates";
const char CHT_LAST_CHECK_DATE[] = "lastCheckDate";

const char CHT_DEFAULT_CONTEXT[] = "cpp";
const char CHT_DEFAULT_URL[] = "https://cht.sh";
const char UPDATES_URL[]   = "https://api.github.com/repos/pozemka/cheatsh-qtcreator/releases/latest";

const unsigned int UPDATE_INTERVAL = 7;

} // namespace Constants
} // namespace CheatSh
