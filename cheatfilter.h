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
    void prepareSearch(const QString &entry) override;
    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future,
                                         const QString &entry) override;
    void accept(Core::LocatorFilterEntry selection,
                QString *newText, int *selectionStart, int *selectionLength) const override;

    void refresh(QFutureInterface<void> &) override {}

signals:
    void query(const QString& text) const;

private:
    void sendSearchRequest();
    //
    std::unique_ptr<QNetworkAccessManager> network_manager_;
    std::unique_ptr<QNetworkReply> reply_main_;
    std::unique_ptr<QMutex> net_mutex_;
    std::unique_ptr<QWaitCondition> request_finished_;
    const Settings* settings_ = nullptr;
    bool exiting_ = false;
    QTimer search_rate_limiter_;
    QString search_request_new_;
    QString search_request_pending_;
};

}}


#endif // CHEATFILTER_H
