#include "cheatoutputplane.h"
#include "settings.h"

#include <ansi_esc2html.h>

#include <QLabel>
#include <QString>
#include <QTextBrowser>

namespace CheatSh {
namespace Internal {

CheatOutputPlane::CheatOutputPlane(const Settings* settings, QObject* parent) :
    Core::IOutputPane(parent),
    settings_(settings),
    ansi2html_(std::make_unique<ANSI_SGR2HTML>())
{
    index_label_ = std::make_unique<QLabel>("");
    index_label_->setToolTip(tr("Number of answer"));
    toolbar_widgets_.append(index_label_.get());
}

CheatOutputPlane::~CheatOutputPlane()
{
    toolbar_widgets_.clear();
}

void CheatOutputPlane::displayANSI(const QString& result)
{
    std::string html = ansi2html_->simpleParse(result.toStdString());
    displayHtml( QString::fromUtf8( html.data(), static_cast<int>(html.size()) ) );
}

void CheatOutputPlane::displayHtml(const QString &html)
{
    browser_->setHtml(html);
    popup(ModeSwitch);
}

void CheatOutputPlane::setNextAvaliable(bool avaliable)
{
    next_avaliable_ = avaliable;
    emit navigateStateUpdate();
}

void CheatOutputPlane::setPrevAvaliable(bool avaliable)
{
    prev_avaliable_ = avaliable;
    emit navigateStateUpdate();
}

void CheatOutputPlane::setIndex(int index)
{
    index_ = index;
    if(index_label_) {
        index_label_->setNum(index_);
    }
}

QWidget* CheatOutputPlane::outputWidget(QWidget* parent)
{
    browser_ = new QTextBrowser(parent);
    browser_->setOpenExternalLinks(true);
    return browser_;
}

QList<QWidget*> CheatOutputPlane::toolBarWidgets() const
{
    //TODO: can add additional tool buttons. Such as "history prev/next", "change formatting", even search input field
    return toolbar_widgets_;
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
    return next_avaliable_ | prev_avaliable_;
}

bool CheatOutputPlane::canNext() const
{
    return next_avaliable_;
}

bool CheatOutputPlane::canPrevious() const
{
    return prev_avaliable_;
}

void CheatOutputPlane::goToNext()
{
    emit requestedNext();
}

void CheatOutputPlane::goToPrev()
{
    emit requestedPrev();
}

}   // namespace Internal
}   // namespace CheatSh
