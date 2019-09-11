#include "cheatoutputplane.h"

#include <QTextBrowser>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

namespace CheatSh {
namespace Internal {

CheatOutputPlane::CheatOutputPlane(const Settings* settings) :
    settings_(settings)

{
    network_manager_ = new QNetworkAccessManager(this);
      connect(network_manager_, &QNetworkAccessManager::finished,
              [this](QNetworkReply* rep){
          if(text_browser_) {
              qDebug("finished");
              for (auto header_name: rep->rawHeaderList()) {
                  qDebug("header '%s'", rep->rawHeader(header_name).constData());
              }
              text_browser_->setText( QString::fromUtf8(rep->readAll()) );
          }
      });
}

CheatOutputPlane::~CheatOutputPlane()
{

}

void CheatOutputPlane::find(QString text)
{
    return;
    network_manager_->get(
                QNetworkRequest(
                    QUrl::fromUserInput(
                        QString("cht.sh/cpp/%1")
                        .arg(text.replace(' ', '-'))
                    )
                )
    );
}

QWidget*CheatOutputPlane::outputWidget(QWidget* parent)
{
    text_browser_ = new QTextBrowser(parent);
    text_browser_->setText("Loading,,,");
//    network_manager_->get(QNetworkRequest(QUrl::fromUserInput("cht.sh/cpp/reverse+a+list")));
    return text_browser_;
}

QList<QWidget*> CheatOutputPlane::toolBarWidgets() const
{
    return QList<QWidget*>();
}

QString CheatOutputPlane::displayName() const
{
    return tr("Cheat sheet QtC");
}

int CheatOutputPlane::priorityInStatusBar() const
{
    return 0;
}

void CheatOutputPlane::clearContents()
{

}

void CheatOutputPlane::visibilityChanged(bool visible)
{
    text_browser_->setVisible(visible);
}

void CheatOutputPlane::setFocus()
{
    text_browser_->setFocus();
}

bool CheatOutputPlane::hasFocus() const
{
    if(text_browser_)
        return text_browser_->hasFocus();

    return false;
}

bool CheatOutputPlane::canFocus() const
{
    return true;
}

bool CheatOutputPlane::canNavigate() const
{
    return false;
}

bool CheatOutputPlane::canNext() const
{
    return false;
}

bool CheatOutputPlane::canPrevious() const
{
    return false;
}

void CheatOutputPlane::goToNext()
{

}

void CheatOutputPlane::goToPrev()
{

}

}   // namespace Internal
}   // namespace CheatSh
