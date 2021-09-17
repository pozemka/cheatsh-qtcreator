#ifndef CHEATFILTER_H
#define CHEATFILTER_H

#include <coreplugin/locator/ilocatorfilter.h>
#include <coreplugin/icore.h>
//#include <coreplugin/messagemanager.h>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QWaitCondition>

#include <memory>

class QNetworkReply;
class QMutex;
class QWaitCondition;

namespace CheatSh {
namespace Internal {

class Settings;

class CheatFilter : public Core::ILocatorFilter
{
    Q_OBJECT
public:
    CheatFilter(const Settings* settigns);
    ~CheatFilter();
    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future,
                                             const QString &entry) override;
        void accept(Core::LocatorFilterEntry selection,
                    QString *newText, int *selectionStart, int *selectionLength) const override;

        void refresh(QFutureInterface<void> &) override {}
signals:
    void query(const QString& text) const;

private:
    const Settings* settings_ = nullptr;
};

}}


#endif // CHEATFILTER_H
