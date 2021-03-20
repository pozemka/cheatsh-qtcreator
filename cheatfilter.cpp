#include "cheatfilter.h"

#include "settings.h"
#include "cheatshconstants.h"

#include <QDebug>
#include <QMutex>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QThread>
#include <QWaitCondition>

using Core::LocatorFilterEntry;

namespace CheatSh {
namespace Internal {

CheatFilter::CheatFilter(const Settings* settigns) :
    network_manager_(std::make_unique<QNetworkAccessManager>(this)),
    settings_(settigns)
{
    setId("cheat.sh");
    setDisplayName(tr("Search cheat.sh"));  // Text in Locator
    setShortcutString("ch");
    setPriority(High);
    setIncludedByDefault(false);
    net_mutex_ = std::make_unique<QMutex>();
    request_finished_ = std::make_unique<QWaitCondition>();
    search_rate_limiter_.setInterval(Constants::SEARCH_RATE_LIMIT);
    search_rate_limiter_.setSingleShot(true);
    connect(&search_rate_limiter_, &QTimer::timeout, this, [](){

    });
}

CheatFilter::~CheatFilter()
{
    exiting_ = true;
    if (reply_main_)
        reply_main_->abort();
    request_finished_->wakeAll();
    net_mutex_->lock();
    net_mutex_->unlock();
}

void CheatFilter::prepareSearch(const QString &entry)
{
    QNetworkRequest request;
    QString question(entry);
    static const QRegularExpression re(R"(^\/(\w+)\/)");
    QString context = settings_->context;
    QRegularExpressionMatch match = re.match(question);
    if(match.hasMatch()) {
        context = match.captured(1);
        question.remove(re);
    }
    question.replace(' ', '+');
    auto buildRequest = [&]() -> QUrl
    {
        return QUrl::fromUserInput(
                    QString("%1/%2/%3?action=suggest")
                    .arg(settings_->url.toString(QUrl::PrettyDecoded|QUrl::StripTrailingSlash),
                         context,
                         question)
                    );
    };
    request.setUrl(buildRequest());
    request.setRawHeader("User-Agent", "User-Agent: curl/7.60.0");

    reply_main_.reset(network_manager_->get(request));

    connect(reply_main_.get(), &QNetworkReply::finished, [this](){
//        qDebug() << "finished:";
       request_finished_->wakeAll();
    });
    connect(reply_main_.get(), QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
          [=](QNetworkReply::NetworkError code){
        qWarning("CheatFilter::prepareSearch(). Error occured '%d': %s", code, qPrintable(reply_main_->errorString()));
        request_finished_->wakeAll();
    });
}

QList<LocatorFilterEntry> CheatFilter::matchesFor(QFutureInterface<LocatorFilterEntry>& future,
                                                  const QString& entry)
{
    QList<LocatorFilterEntry> value;
    if (!future.isCanceled())
        if (!entry.isEmpty()) // avoid empty entry
            value.append(LocatorFilterEntry(this, entry, QVariant()));

    net_mutex_->lock();
    request_finished_->wait(net_mutex_.get());
    if (exiting_) {
        net_mutex_->unlock();
        return value;
    }
    if (QNetworkReply::NoError == reply_main_->error()) {
        QString reply = QString::fromUtf8(reply_main_->readAll());
        auto results = reply.split('\n');
        // FIXME: probably ask for better server responce codes instead of rely on parsing
        if (!results.isEmpty() && results.first() != QLatin1String("404 NOT FOUND")) {
            for (const auto& result : results){
                if (future.isCanceled())
                    break;
                value.append(LocatorFilterEntry(this, result, QVariant()));
            }
        }
    }
    net_mutex_->unlock();

//    QNetworkRequest request;
//    request.setUrl(QUrl::fromUserInput("cheat.sh/cpp/string+append?action=suggest"));
//    request.setRawHeader("X-Cheatsh-Key", "867dc3ba-e70e-44f6-99b7-3c8b2824ade3");
//    auto reply = network_manager_->get(request);



    //TODO: search history or autocompletion similar to bash implementation of cheat.sh
//        const Qt::CaseSensitivity entryCaseSensitivity = caseSensitivity(entry);
//        for (const QString &cmd : qAsConst(m_commandHistory)) {
//            if (future.isCanceled())
//                break;
//            if (cmd == entry) // avoid repeated entry
//                continue;
//            LocatorFilterEntry filterEntry(this, cmd, QVariant());
//            const int index = cmd.indexOf(entry, 0, entryCaseSensitivity);
//            if (index >= 0) {
//                filterEntry.highlightInfo = {index, entry.length()};
//                value.append(filterEntry);
//            } else {
//                others.append(filterEntry);
//            }
//        }
//    value.append(others);
    return value;
}

void CheatFilter::accept(Core::LocatorFilterEntry selection, QString* newText, int* selectionStart, int* selectionLength) const
{
    Q_UNUSED(selection)
    Q_UNUSED(newText)
    Q_UNUSED(selectionStart)
    Q_UNUSED(selectionLength)
//    qDebug() << "accept" << selection.displayName << *newText << *selectionStart << *selectionLength;   //accept "aaa" "" -1 0
    if(!selection.displayName.isEmpty())
        emit query(selection.displayName);
}

void CheatFilter::sendSearchRequest()
{

}

}}
