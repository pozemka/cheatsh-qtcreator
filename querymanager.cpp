#include "querymanager.h"

#include "cheatshconstants.h"
#include "progressreport.h"
#include "settings.h"

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegularExpression>

namespace CheatSh {
namespace Internal {


QueryManager::QueryManager(const Settings* settigns, QObject* parent) :
    QObject(parent),
    settings_(settigns),
    network_manager_(std::make_unique<QNetworkAccessManager>(this)),
    network_manager_stripped_(std::make_unique<QNetworkAccessManager>(this)),
    progress_report_(std::make_unique<ProgressReport>())
{
    connect(network_manager_.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* rep) {
//        QFile debug_file("debug.txt");
//        debug_file.open(QIODevice::WriteOnly);
//        debug_file.write(rep->readAll());
        QString answer = QString::fromUtf8(rep->readAll());
        answers_cache_.insert(answer_index_, answer);
        progress_report_->increment();
        if(!rep->error()) {
            // Only emit found on successfull requests
            emit found(answer);
        }
        emit indexChanged(answer_index_);   //Index updates even when request failed. Is it ok?
        updatePrevNext();
    });
    connect(network_manager_stripped_.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* rep) {
        QString answer = QString::fromUtf8(rep->readAll());
        stripped_cache_.insert(answer_index_, answer);
        progress_report_->increment();
        if(!rep->error()) {
            // Only emit pasteReady on successfull requests
            emit pasteReady(answer);
        }
    });
    connect(progress_report_.get(), &ProgressReport::cancelRequested, this, &QueryManager::cancelRequests);
}

QueryManager::~QueryManager()
{

}

void QueryManager::search(const QString& question)
{
    question_ = question;
    answer_index_ = 0;
    answers_cache_.clear(); // Caches are clear for every new question
    stripped_cache_.clear();
    query();
}

void QueryManager::requestNext()
{
    if(isRepliesActive()) {
        return; //Do nothing until request finishes
    }

    answer_index_++;
    requestAnswerFromCacheOrQuery(answer_index_);
}

void QueryManager::requestPrev()
{
    if(answer_index_ <= 0)
        return;
    if(isRepliesActive()) {
        return; //Do nothing until request finishes
    }

    answer_index_--;
    requestAnswerFromCacheOrQuery(answer_index_);
}

void QueryManager::cancelRequests()
{
    if(reply_main_)
        reply_main_->abort();
    if(reply_stripped_)
        reply_stripped_->abort();
}

void QueryManager::query()
{
    // Trailing options
    QString options;
    if(!settings_->comments_enabled)
        options.append("?Q");

    // Context override
    static const QRegularExpression re(R"(^\/(\w+)\/)");
    QString context = settings_->context;
    QRegularExpressionMatch match = re.match(question_);
    if(match.hasMatch()) {
        context = match.captured(1);
        question_.remove(re);
    }
    question_.replace(' ', '+');
    QNetworkRequest request;
    auto buildRequest = [&](const QString& options) -> QUrl
    {
        return QUrl::fromUserInput(
                    QString("%1/%2/%3/%4%5")
                    .arg(settings_->url.toString(QUrl::PrettyDecoded|QUrl::StripTrailingSlash),
                         context,
                         question_,
                         QString::number(answer_index_),
                         options)
                    );
    };
    request.setUrl(buildRequest(options));
//    qDebug("%s", qPrintable(request.url().toString()));
    request.setRawHeader("User-Agent", "User-Agent: curl/7.60.0");
    progress_report_->startNew();
    reply_main_.reset(network_manager_->get(request));

//    connect(reply_main_, &QNetworkReply::downloadProgress, [](qint64 received, qint64 total){
//        qDebug("%lld/%lld", received, total);
//        //download progress not used for now
//    });
    connect(reply_main_.get(), &QNetworkReply::errorOccurred, this, [&](QNetworkReply::NetworkError code){
        reportRequestError(code, reply_main_->errorString());
        progress_report_->cancel();
        reply_main_->deleteLater();
    });
    request.setUrl(buildRequest("?TQ"));    // No formatting, No comments
    reply_stripped_.reset(network_manager_stripped_->get(request));    // FIXME: probably postpone second request after results of first one? That way probably reduce server load thanks to cached result. But may lead to no or wrong paste data due to delay. NOTE: it seems this "second" request finishes before "first"
}

void QueryManager::requestAnswerFromCacheOrQuery(int index)
{
    if(index < 0
            || answers_cache_.size() <= index
            || stripped_cache_.size() <= index
            || answers_cache_.at(index).isEmpty()   // To retry previously failed requests
            || stripped_cache_.at(index).isEmpty()) {
        query();
        return;
    }

    emit found(answers_cache_.at(index));
    emit pasteReady(stripped_cache_.at(index));
    emit indexChanged(index);
    updatePrevNext();
}

void QueryManager::updatePrevNext()
{
    if(question_.isEmpty()) {
        emit nextAvaliable(false);
        emit prevAvaliable(false);
    } else {
        emit nextAvaliable(true); //It seems next is always avaliable if there is question

        if(answer_index_ > 0)
            emit prevAvaliable(true);
        else
            emit prevAvaliable(false);
    }
}

bool QueryManager::isRepliesActive() const
{
    return reply_main_ && reply_stripped_
            && (reply_main_->isRunning() || reply_stripped_->isRunning());
}

void QueryManager::reportRequestError(int error_code, const QString& error_text)
{
    QString err = tr("<b>An error occurred during cheat sheet request (code %1):</b><br /> %2.").arg(error_code).arg(error_text);
//    qWarning("Error during request: %d - %s", error_code, qPrintable(error_text));
    emit errorOccurred(err);
}

} // namespace Internal
} // namespace CheatSh
