#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include "settings.h"
#include "cheatshconstants.h"

#include <QDebug>

namespace CheatSh {
namespace Internal {

OptionsDialog::OptionsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    ui->contextLineEdit->setPlaceholderText(Constants::CHT_DEFAULT_CONTEXT);
    ui->urlLineEdit->setPlaceholderText(Constants::CHT_DEFAULT_URL);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::setSettings(const Settings& settings)
{
    ui->contextLineEdit->setText(settings.context);
    ui->urlLineEdit->setText(settings.url.toString());
    ui->checkBox_comments->setChecked(settings.comments_enabled);
    ui->checkBox_updates->setChecked(settings.check_updates);
}

Settings OptionsDialog::settings()
{
    Settings settings;
    //Setting default values if user input is empty
    settings.context = secondIfFirstIsEmpty(ui->contextLineEdit->text(),
                                            QString(Constants::CHT_DEFAULT_CONTEXT));
    settings.url = secondIfFirstIsEmpty(QUrl::fromUserInput(ui->urlLineEdit->text()),
                                        QUrl::fromUserInput(Constants::CHT_DEFAULT_URL));
    settings.comments_enabled = ui->checkBox_comments->isChecked();
    settings.check_updates = ui->checkBox_updates->isChecked();
    return settings;
}

}   // namespace Internal
}   // namespace CheatSh
