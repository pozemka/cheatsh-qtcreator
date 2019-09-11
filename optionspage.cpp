#include "optionspage.h"

#include "optionsdialog.h"

namespace CheatSh {
namespace Internal {

OptionsPage::OptionsPage(const Settings& settings, QObject* parent) :
    Core::IOptionsPage(parent),
    widget_(nullptr),
    settings_(settings)
{
    setId("CheatShSettings");
    setDisplayName(tr("Cheat.sh")); //tab name on the top
    setCategory("Cheat.sh");
    setDisplayCategory(tr("Cheat.sh"));  //displayed on the left
    //TODO: icon
//    setCategoryIcon(Utils::Icon({{":/todoplugin/images/settingscategory_todo.png",
    //                    Utils::Theme::PanelTextColorDark}}, Utils::Icon::Tint));
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

}

void OptionsPage::finish()
{

}

}   // namespace CheatSh
}   // namespace Internal
