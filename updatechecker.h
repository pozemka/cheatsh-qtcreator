#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QObject>
#include <QString>

#include <memory>

class QNetworkAccessManager;

namespace CheatSh {
namespace Internal {

class Settings;

class UpdateChecker : public QObject
{
    Q_OBJECT
public:
    UpdateChecker(Settings *settigns, QObject* parent = nullptr);
    ~UpdateChecker() override;

    void checkUpdatesIfPossible();

signals:
    void updateAvaliable(const QString& update_text);

private:
    Settings* settings_ = nullptr;
    std::unique_ptr<QNetworkAccessManager> network_manager_;
};

} // namespace Internal
} // namespace CheatSh

#endif // UPDATECHECKER_H
