#ifndef CHEATSH_H
#define CHEATSH_H

#include <QHash>
#include <QObject>
#include <QVector>

#include <memory>

class QNetworkAccessManager;
class QNetworkReply;

namespace CheatSh {
namespace Internal {

class Settings;

/**
 * @brief The CheatSh class is used to interact with cheat.sh server
 */
class QueryManager : public QObject
{
    Q_OBJECT
public:
    explicit QueryManager(const Settings* settigns, QObject *parent);
    ~QueryManager() override;

signals:
    void found(const QString& result);
    void pasteReady(const QString& result);
    void nextAvaliable(bool avaliable);
    void prevAvaliable(bool avaliable);
    void indexChanged(int index);

public slots:
    void search(QString text/*intentional copy*/);
    void requestNext();
    void requestPrev();

private:
    void query();
    /**
     * @brief If answer with index avaliable in cache returns true
     * and emits found signal and indexChanged signal. Otherwise
     * returns false
     * @param index Answer index.
     * @return true if Answer with index is in cache
     */
    bool tryAnswerFromCache(int index);
    const Settings* settings_ = nullptr;
    QString question_;
    std::unique_ptr<QNetworkAccessManager> network_manager_;
    std::unique_ptr<QNetworkAccessManager> network_manager_stripped_;
    int answer_index_ = 0;
    QVector<QString> answers_cache_;
    QNetworkReply* reply_ = nullptr;  //!< to track request progress
    bool reply_in_process_ = false; //!< reply_ is deleted on completion so using separate variable to check for finished state
};

} // namespace Internal
} // namespace CheatSh

#endif // CHEATSH_H
