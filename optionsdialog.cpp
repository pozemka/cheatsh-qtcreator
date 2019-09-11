#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include "settings.h"

namespace CheatSh {
namespace Internal {

OptionsDialog::OptionsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::setSettings(const Settings& settings)
{

}

Settings OptionsDialog::settings()
{
    Settings settings;
    return settings;
}

}   // namespace Internal
}   // namespace CheatSh
