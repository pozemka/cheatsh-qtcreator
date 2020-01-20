#ifndef CHEATSH_H
#define CHEATSH_H

#include <QObject>

#include <memory>

class QNetworkAccessManager;

namespace CheatSh {
namespace Internal {

class Settings;

/**
 * @brief The CheatSh class is used to interact with cheat.sh server
 */
class Cheat : public QObject
{
    Q_OBJECT
public:
    explicit Cheat(const Settings* settigns, QObject *parent);
    ~Cheat() override;

signals:
    void found(const QString& result);
    void pasteReady(const QString& result);

public slots:
    void search(QString text/*intentional copy*/);

private:
    const Settings* settings_ = nullptr;
    std::unique_ptr<QNetworkAccessManager> network_manager_;
    std::unique_ptr<QNetworkAccessManager> network_manager_stripped_;
};

} // namespace Internal
} // namespace CheatSh

#endif // CHEATSH_H
