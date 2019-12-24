#include "cheatsh.h"

#include "settings.h"

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace CheatSh {
namespace Internal {

CheatSh::CheatSh(const Settings* settigns, QObject* parent) : QObject(parent), settings_(settigns)
{
    network_manager_ = std::make_unique<QNetworkAccessManager>(this);
    connect(network_manager_.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* rep) {
                qDebug("reply");
                for (auto header_name: rep->rawHeaderList()) {
                    qDebug("header '%s'", rep->rawHeader(header_name).constData());
                }
//                QFile debug_file("debug.txt");
//                debug_file.open(QIODevice::WriteOnly);
//                debug_file.write(rep->readAll());
                emit found(QString::fromUtf8(rep->readAll()));
            });

}

CheatSh::~CheatSh()
{

}

void CheatSh::search(QString text)
{
    QNetworkRequest request;
    request.setUrl(QUrl::fromUserInput(
                       QString("%1/cpp/%2") // ?T - no coloring
                       // TODO: replace cpp with settings_->context or something
                       .arg(settings_->url.toString(QUrl::PrettyDecoded|QUrl::StripTrailingSlash))
                       .arg(text.replace(' ', '+'))
                   ));
    qDebug("%s", qPrintable(request.url().toString()));
//    request.setRawHeader("User-Agent", "User-Agent: curl/7.60.0");
    network_manager_->get(request);
}

} // namespace Internal
} // namespace CheatSh
