#include "optionspage.h"

#include <utility>

#include "optionsdialog.h"

namespace CheatSh {
namespace Internal {

OptionsPage::OptionsPage(Settings  settings, QObject* parent) :
    Core::IOptionsPage(parent),
    widget_(nullptr),
    settings_(std::move(settings))
{
    setId("CheatShSettings");
    setDisplayName(tr("General")); //tab name on the top
    setCategory("Cheat.sh");
    setDisplayCategory(tr("Cheat.sh"));  //displayed on the left
    setCategoryIcon(Utils::Icon({{":/cheatshplugin/settings_category.png",
                        Utils::Theme::PanelTextColorDark}}, Utils::Icon::Tint));
}

void OptionsPage::setSettings(const Settings& settings)
{
    settings_ = settings;
}

QWidget* OptionsPage::widget()
{
    if(!widget_) {
        widget_ = new OptionsDialog;
        widget_->setSettings(settings_);
    }
    return widget_;
}

void OptionsPage::apply()
{
    Settings new_settings = widget_->settings();
    if(new_settings != settings_) {
        settings_ = new_settings;
        emit settingsChanged(settings_);
    }
}

void OptionsPage::finish()
{
    delete widget_;
}

}   // namespace CheatSh
}   // namespace Internal
