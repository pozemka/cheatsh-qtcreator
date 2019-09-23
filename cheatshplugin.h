#pragma once

#include "cheatsh_global.h"
#include "cheatoutputplane.h"
#include "settings.h"

#include <extensionsystem/iplugin.h>

namespace CheatSh {
namespace Internal {

class OptionsPage;

class CheatShPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "CheatSh.json")

public:
    CheatShPlugin();
    ~CheatShPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void changeSettings(const Settings &settings);

private:
    void triggerAction();
    void createOptionsPage();
    void createOutputPane();
    void createMenus();

    CheatOutputPlane* cheat_out_plane_; //TODO: change to smart pointers later
    OptionsPage* options_page_;
    Settings settings_;
    QAction* action_cheat_sh_;
};

} // namespace Internal
} // namespace CheatSh
