#pragma once

#include "settings.h"

#include <extensionsystem/iplugin.h>

#include <memory>

class QAction;

namespace CheatSh {
namespace Internal {

class OptionsPage;
class Cheat;
class CheatFilter;
class CheatOutputPlane;
class UpdateChecker;

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
    void createMenus();

    Settings settings_;
    std::unique_ptr<CheatFilter> cheat_filter_;
    UpdateChecker* update_checker_ = nullptr;
    QAction* action_cheat_sh_ = nullptr;
    CheatOutputPlane* out_plane_ = nullptr;
    OptionsPage* options_page_ = nullptr;
    Cheat* cheat_sh_ = nullptr;
};

} // namespace Internal
} // namespace CheatSh
