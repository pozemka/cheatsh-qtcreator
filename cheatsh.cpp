#include "cheatsh.h"

#include "settings.h"

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegularExpression>

namespace CheatSh {
namespace Internal {

Cheat::Cheat(const Settings* settigns, QObject* parent) : QObject(parent), settings_(settigns)
{
    network_manager_ = std::make_unique<QNetworkAccessManager>(this);
    connect(network_manager_.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* rep) {
//                QFile debug_file("debug.txt");
//                debug_file.open(QIODevice::WriteOnly);
//                debug_file.write(rep->readAll());
                emit found(QString::fromUtf8(rep->readAll()));
                rep->deleteLater();
            });

}

Cheat::~Cheat()
{

}

void Cheat::search(QString text)
{
    // Trailing options
    QString options;
    if(!settings_->comments_enabled)
        options.append("?Q");

    // Context override
    static const QRegularExpression re(R"(^\/(\w+)\/)");
    QString context = settings_->context;
    QRegularExpressionMatch match = re.match(text);
    if(match.hasMatch()) {
        context = match.captured(1);
        text.remove(re);
    }
    QNetworkRequest request;
    request.setUrl(QUrl::fromUserInput(
                       QString("%1/%2/%3%4") // ?T - no coloring
                       .arg(settings_->url.toString(QUrl::PrettyDecoded|QUrl::StripTrailingSlash),
                            context,
                            text.replace(' ', '+'),
                            options)
                   ));
    qDebug("%s", qPrintable(request.url().toString()));
    request.setRawHeader("User-Agent", "User-Agent: curl/7.60.0");
    network_manager_->get(request);
}

} // namespace Internal
} // namespace CheatSh
