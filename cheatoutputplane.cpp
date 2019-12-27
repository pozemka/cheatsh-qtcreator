#include "cheatoutputplane.h"

#include <QTextBrowser>
#include <QWebEngineView>
#include <QString>

#include <ansi_esc2html.h>

namespace CheatSh {
namespace Internal {

CheatOutputPlane::CheatOutputPlane(const Settings* settings, QObject* parent) :
    Core::IOutputPane(parent),
    settings_(settings),
    ansi2html_(std::make_unique<ANSI_SGR2HTML>())
{

}

CheatOutputPlane::~CheatOutputPlane()
{

}

void CheatOutputPlane::displayResult(const QString& result)
{
    auto sts = ansi2html_->simpleParse(result.toStdString());
    browser_->setHtml(QString::fromUtf8(sts.data(), sts.size()));
    popup(NoModeSwitch);
}

QWidget*CheatOutputPlane::outputWidget(QWidget* parent)
{

    browser_ = new QTextBrowser(parent);
    browser_->setHtml(tr("TODO: plugin's own help text"));

    return browser_;
}

QList<QWidget*> CheatOutputPlane::toolBarWidgets() const
{
    return QList<QWidget*>();
}

QString CheatOutputPlane::displayName() const
{
    return tr("cheat.sh");
}

int CheatOutputPlane::priorityInStatusBar() const
{
    return 0;
}

void CheatOutputPlane::clearContents()
{
    browser_->clear();
}

void CheatOutputPlane::visibilityChanged(bool visible)
{
    browser_->setVisible(visible);
}

void CheatOutputPlane::setFocus()
{
    browser_->setFocus();
}

bool CheatOutputPlane::hasFocus() const
{
    if(browser_)
        return browser_->hasFocus();

    return false;
}

bool CheatOutputPlane::canFocus() const
{
    return true;
}

bool CheatOutputPlane::canNavigate() const
{
    return false;
}

bool CheatOutputPlane::canNext() const
{
    return false;
}

bool CheatOutputPlane::canPrevious() const
{
    return false;
}

void CheatOutputPlane::goToNext()
{

}

void CheatOutputPlane::goToPrev()
{

}

}   // namespace Internal
}   // namespace CheatSh
