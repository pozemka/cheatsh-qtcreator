#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QWidget>

namespace CheatSh {
namespace Internal {

namespace Ui {
    class OptionsDialog;
}
class Settings;

class OptionsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

    void setSettings(const Settings& settings);
    Settings settings();

private:
    Ui::OptionsDialog *ui;
};

}   // namespace Internal
}   // namespace CheatSh

#endif // OPTIONSDIALOG_H
