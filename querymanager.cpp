#include "querymanager.h"

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
    network_manager_stripped_(std::make_unique<QNetworkAccessManager>(this))
{
    connect(network_manager_.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* rep) {
//        QFile debug_file("debug.txt");
//        debug_file.open(QIODevice::WriteOnly);
//        debug_file.write(rep->readAll());
        QString answer = QString::fromUtf8(rep->readAll());
        answers_cache_.insert(answer_index_, answer);
        emit found(answer);
        emit indexChanged(answer_index_);
        updatePrevNext();
    });
    connect(network_manager_stripped_.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* rep) {
        QString answer = QString::fromUtf8(rep->readAll());
        stripped_cache_.insert(answer_index_, answer);
        emit pasteReady(answer);
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
    if(!tryAnswerFromCache(answer_index_)) {
        query(); // request next if answer not cached
    } else {
        updatePrevNext();
    }
}

//Может вектор зменить на хэш и тогда прекращать активные запросы чтобы можно было быстро прокликать к какоуму-то ответу. И тогда можно просто проверять, есть ли такой индекс в хэше и если есть возвращать а если нет делать запрос. Кажется будет проще.

void QueryManager::requestPrev()
{
    if(answer_index_ <= 0)
        return;
    if(isRepliesActive()) {
        return; //Do nothing until request finishes
    }

    answer_index_--;
    tryAnswerFromCache(answer_index_);
    updatePrevNext();
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
    auto reply_old = reply_main_;
    reply_main_ = network_manager_->get(request);
    delete reply_old;
    request.setUrl(buildRequest("?TQ"));    // No formatting, No comments
    reply_old = reply_stripped_;
    reply_stripped_ = network_manager_stripped_->get(request);    // FIXME: probably postpone second request after results of first one? That way probably reduce server load thanks to cached result. But may lead to no or wrong paste data due to delay.
    delete reply_old;
}

bool QueryManager::tryAnswerFromCache(int index)
{
    if(index < 0 || answers_cache_.size() <= index)
        return false;

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

} // namespace Internal
} // namespace CheatSh
