#ifndef CHEATOUTPUTPLANE_H
#define CHEATOUTPUTPLANE_H

#include <coreplugin/ioutputpane.h>

#include <memory>

class ANSI_SGR2HTML;

class QTextBrowser;

namespace CheatSh {
namespace Internal {

class Settings;

class CheatOutputPlane : public Core::IOutputPane
{
    Q_OBJECT
public:
    CheatOutputPlane(const Settings* settings/*non-owning*/, QObject* parent);
    ~CheatOutputPlane();

public slots:
    void displayANSI(const QString& result);
    void displayHtml(const QString& html);

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
    QTextBrowser* browser_ = nullptr;
    const Settings* settings_ = nullptr;
    std::unique_ptr<ANSI_SGR2HTML> ansi2html_;
};

}   // namespace Internal
}   // namespace CheatSh

#endif // CHEATOUTPUTPLANE_H
