#ifndef CHEATFILTER_H
#define CHEATFILTER_H

#include <coreplugin/locator/ilocatorfilter.h>
#include <coreplugin/icore.h>
//#include <coreplugin/messagemanager.h>
namespace CheatSh {
namespace Internal {

class CheatFilter : public Core::ILocatorFilter
{
    Q_OBJECT
public:
    CheatFilter();
    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future,
                                         const QString &entry) override;
    void accept(Core::LocatorFilterEntry selection,
                QString *newText, int *selectionStart, int *selectionLength) const override;

    void refresh(QFutureInterface<void> &) override {}

signals:
    void query(const QString& text) const;

private:
    //
};

}}


#endif // CHEATFILTER_H
