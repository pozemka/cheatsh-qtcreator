#include "querymanager.h"

#include "cheatshconstants.h"
#include "settings.h"

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegularExpression>

namespace CheatSh {
namespace Internal {

/**
 * @brief The ProgressReport class is a basic progress report wrapper
 * For now only request loading is reported so it is fine to place it right here.
 */
class ProgressReport
{
public:

    //TODO:     QObject::connect(progress, &Core::FutureProgress::canceled, this, [this]{stop({});});
    void startNew()
    {
        progress_.reset();
        progress_ = std::make_unique<QFutureInterface<void>>();
        progress_->setProgressRange(0, 2);
        Core::ProgressManager::addTask( progress_->future(),
                                        QObject::tr( "Cheat.sh: Requesting cheat sheet" ),
                                        CheatSh::Constants::TASK_ID_REQUEST );
        progress_->reportStarted();
    }
    void increment()
    {
        if(progress_) {
            progress_->setProgressValue(progress_->progressValue()+1);
            if(progress_->progressValue() == progress_->progressMaximum())
                progress_->reportFinished();
        }
    }
    void cancel()
    {
        if(progress_) {
            progress_->reportCanceled(); // It seems cancel() and reportCanceled do same thing
            progress_->reportFinished(); // reportFinished should follow reportCanceled
            //FIXME: Minor: shadow of report popup stays over Cheat.sh panel. Looks like update() should clear it. Prbably will be solved when error displayed in panel.
        }
    }
private:
    std::unique_ptr<QFutureInterface<void>> progress_;
};

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
    if(!tryAnswerFromCache(answer_index_)) { // TODO: merge this if-else to tryAnswerFromCache ?
        query(); // request next if answer not cached
    } else {
        updatePrevNext();
    }
}

void QueryManager::requestPrev()
{
    if(answer_index_ <= 0)
        return;
    if(isRepliesActive()) {
        return; //Do nothing until request finishes
    }

    answer_index_--;
    if(!tryAnswerFromCache(answer_index_)) { // TODO: merge this if-else to tryAnswerFromCache ?
        query(); // request prev if answer not cached
    } else {
        updatePrevNext();
    }
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
    connect(reply_main_.get(), static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [&](QNetworkReply::NetworkError code){
        //TODO: display error message in Cheat.sh panel
        reportRequestError(reply_main_->errorString());
        progress_report_->cancel();
    });
    request.setUrl(buildRequest("?TQ"));    // No formatting, No comments
    reply_stripped_.reset(network_manager_stripped_->get(request));    // FIXME: probably postpone second request after results of first one? That way probably reduce server load thanks to cached result. But may lead to no or wrong paste data due to delay.
}

bool QueryManager::tryAnswerFromCache(int index)
{
    if(index < 0
            || answers_cache_.size() <= index
            || stripped_cache_.size() <= index
            || answers_cache_.at(index).isEmpty()   // To retry previously failed requests
            || stripped_cache_.at(index).isEmpty()) {
        return false;
    }

    emit found(answers_cache_.at(index));
    emit pasteReady(stripped_cache_.at(index));
    emit indexChanged(index);
    return true;
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

void QueryManager::reportRequestError(const QString& error_text)
{
    QString err = tr("An error occurred during the request:\n%1").arg(error_text);
//    qWarning("%s", qPrintable(err));
    emit found(err);    //TODO: use different signal to report errors
}

} // namespace Internal
} // namespace CheatSh
