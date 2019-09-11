#pragma once

#include "cheatsh_global.h"
#include "cheatoutputplane.h"

#include <extensionsystem/iplugin.h>

namespace CheatSh {
namespace Internal {

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
    CheatOutputPlane* cheat_out_plane_;
};

} // namespace Internal
} // namespace CheatSh
