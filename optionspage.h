#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include "settings.h"

#include <coreplugin/dialogs/ioptionspage.h>

#include <QPointer>

namespace CheatSh {
namespace Internal {

class OptionsDialog;

class OptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    OptionsPage(Settings settings, QObject* parent);

    void setSettings(const Settings& settings);
    QWidget* widget() override;
    void apply() override;
    void finish() override;

signals:
    void settingsChanged(const CheatSh::Internal::Settings& settings);

private:
    QPointer<OptionsDialog> widget_;
    Settings settings_;
};

}   // namespace Internal
}   // namespace CheatSh

#endif // OPTIONSPAGE_H
