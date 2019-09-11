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

private:
    void triggerAction();
    void createOptionsPage();

    CheatOutputPlane* cheat_out_plane_;
    OptionsPage* options_page_;
    Settings settings_;
};

} // namespace Internal
} // namespace CheatSh
