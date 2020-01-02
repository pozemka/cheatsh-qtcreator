#include "updatechecker.h"

#include <QDate>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QVersionNumber>

#include <coreplugin/icore.h>

#include "cheatshconstants.h"
#include "settings.h"

using namespace Core;

namespace CheatSh {
namespace Internal {

UpdateChecker::UpdateChecker(Settings *settigns, QObject *parent) :
    QObject(parent),
    settings_(settigns),
    network_manager_(std::make_unique<QNetworkAccessManager>(this))
{
    connect(network_manager_.get(), &QNetworkAccessManager::finished, [this](QNetworkReply* reply){
        QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
        if(jsdoc.isNull())
            return;
        settings_->last_check_date = QDate::currentDate();
        QJsonObject jsobj = jsdoc.object();
        const QLocale locale(ICore::userInterfaceLanguage());
        QString version = jsobj.value("tag_name").toString();
        QVersionNumber remote_version = QVersionNumber::fromString(version);
        QVersionNumber local_version = QVersionNumber::fromString(GIT_VERSION);
//        qDebug() << local_version << remote_version;
        if(local_version >= remote_version)
            return;

        QString update_string = tr("<b>Cheat.sh plugin update avaliable.</b>\n"
                                   "<br />New version: %1 from %2\n"
                                   "<br />Description: %3\n"
                                   "<br /><a href=\"%4\">Download here</a>")
                .arg(version)
                .arg(locale.toString(QDateTime::fromString(jsobj.value("published_at").toString(), Qt::ISODate), QLocale::ShortFormat))
                .arg(jsobj.value("body").toString())
                .arg(jsobj.value("html_url").toString());
        emit updateAvaliable(update_string);
    });
}

UpdateChecker::~UpdateChecker()
{

}

void UpdateChecker::checkUpdatesIfPossible()
{
    if(settings_->check_updates &&
            settings_->last_check_date.daysTo(QDate::currentDate()) >=7 ) {
        network_manager_->get(QNetworkRequest(QUrl(CheatSh::Constants::UPDATES_URL)));
    }
}

} // namespace Internal
} // namespace CheatSh
