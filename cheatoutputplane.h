#ifndef CHEATOUTPUTPLANE_H
#define CHEATOUTPUTPLANE_H

#include "settings.h"

#include <coreplugin/ioutputpane.h>

#include <memory>

class ANSI_SGR2HTML;

class QTextBrowser;
class QWebEngineView;

namespace CheatSh {
namespace Internal {

class CheatOutputPlane : public Core::IOutputPane
{
    Q_OBJECT
public:
    CheatOutputPlane(const Settings* settings);
    ~CheatOutputPlane();
    //FIXME: очевидно что искалка, настрйоки, это отображение, и управление (которое в cheatshpligin.cpp) должны быть отдельно. Сейчас для проверки идеи пойдёт и так:
    //FIXME: ещё нужно навтыкать всякие проверки на то что CurrentEditor вообще существует и т.п. на 0 указатели.
    //https://doc-snapshots.qt.io/qtcreator-extending/plugin-lifecycle.html
public slots:
    void displayResult(const QString& result);

    // IOutputPane interface
public:
    QWidget* outputWidget(QWidget* parent);
    QList<QWidget*> toolBarWidgets() const;
    QString displayName() const;
    int priorityInStatusBar() const;
    void clearContents();
    void visibilityChanged(bool visible);
    void setFocus();
    bool hasFocus() const;
    bool canFocus() const;
    bool canNavigate() const;
    bool canNext() const;
    bool canPrevious() const;
    void goToNext();
    void goToPrev();

private:
//    QWebEngineView* browser_ = nullptr;
    QTextBrowser* browser_ = nullptr;
    const Settings* settings_ = nullptr;
    std::unique_ptr<ANSI_SGR2HTML> ansi2html_;
};

}   // namespace Internal
}   // namespace CheatSh

#endif // CHEATOUTPUTPLANE_H
