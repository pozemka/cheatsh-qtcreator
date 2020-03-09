#pragma once

#include "settings.h"

#include <extensionsystem/iplugin.h>

#include <memory>

class QAction;

namespace CheatSh {
namespace Internal {

class OptionsPage;
class QueryManager;
class CheatFilter;
class CheatOutputPlane;
class UpdateChecker;

class CheatShPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "CheatSh.json")

public:
    CheatShPlugin();
    ~CheatShPlugin() override;

    bool initialize(const QStringList &arguments, QString *errorString) override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

private slots:
    void changeSettings(const CheatSh::Internal::Settings &settings);

private:
    void createMenus();

    Settings settings_;
    std::unique_ptr<CheatFilter> cheat_filter_;
    UpdateChecker* update_checker_ = nullptr;
    QAction* action_cheat_sh_ = nullptr;
    QAction* action_paste_ = nullptr;
    CheatOutputPlane* out_plane_ = nullptr;
    OptionsPage* options_page_ = nullptr;
    QueryManager* cheat_sh_ = nullptr;
    QString paste_value_;
};

} // namespace Internal
} // namespace CheatSh
