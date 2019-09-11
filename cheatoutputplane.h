#ifndef CHEATOUTPUTPLANE_H
#define CHEATOUTPUTPLANE_H

#include "settings.h"

#include <coreplugin/ioutputpane.h>

#include <memory>

class QNetworkAccessManager;
class QTextBrowser;

namespace CheatSh {
namespace Internal {

class CheatOutputPlane : public Core::IOutputPane
{
public:
    CheatOutputPlane(const Settings* settings);
    ~CheatOutputPlane();
    //FIXME: очевидно что искалка, настрйоки, это отображение, и управление (которое в cheatshpligin.cpp) должны быть отдельно. Сейчас для проверки идеи пойдёт и так:
    //FIXME: ещё нужно навтыкать всякие проверки на то что CurrentEditor вообще существует и т.п. на 0 указатели.
    //https://doc-snapshots.qt.io/qtcreator-extending/plugin-lifecycle.html
    void find(QString text);    //копия специально

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
    QTextBrowser* text_browser_ = nullptr;
    QNetworkAccessManager* network_manager_ = nullptr;
    const Settings* settings_ = nullptr;
};

}   // namespace Internal
}   // namespace CheatSh

#endif // CHEATOUTPUTPLANE_H
