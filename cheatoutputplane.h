#ifndef CHEATOUTPUTPLANE_H
#define CHEATOUTPUTPLANE_H

#include <coreplugin/ioutputpane.h>

#include <memory>

class ANSI_SGR2HTML;

class QTextBrowser;
class QLabel;

namespace CheatSh {
namespace Internal {

class Settings;

class CheatOutputPlane : public Core::IOutputPane
{
    Q_OBJECT
public:
    CheatOutputPlane(const Settings* settings/*non-owning*/, QObject* parent);
    ~CheatOutputPlane() override;

public slots:
    void displayANSI(const QString& result);
    void displayHtml(const QString& html);
    void setNextAvaliable(bool avaliable);
    void setPrevAvaliable(bool avaliable);
    void setIndex(int index);

    // IOutputPane interface
public:
    QWidget* outputWidget(QWidget* parent) override;
    QList<QWidget*> toolBarWidgets() const override;
    QString displayName() const override;
    int priorityInStatusBar() const override;
    void clearContents() override;
    void visibilityChanged(bool visible) override;
    void setFocus() override;
    bool hasFocus() const override;
    bool canFocus() const override;
    bool canNavigate() const override;
    bool canNext() const override;
    bool canPrevious() const override;
    void goToNext() override;
    void goToPrev() override;

signals:
    void requestedNext();
    void requestedPrev();

private:
    QTextBrowser* browser_ = nullptr;
    std::unique_ptr<QLabel> index_label_;
    QList<QWidget*> toolbar_widgets_;
    const Settings* settings_ = nullptr;
    std::unique_ptr<ANSI_SGR2HTML> ansi2html_;

    bool next_avaliable_ = false;
    bool prev_avaliable_ = false;
    int index_ = 0;
};

}   // namespace Internal
}   // namespace CheatSh

#endif // CHEATOUTPUTPLANE_H
