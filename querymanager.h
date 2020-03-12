#ifndef CHEATSH_H
#define CHEATSH_H

#include <coreplugin/progressmanager/progressmanager.h>

#include <QHash>
#include <QObject>
#include <QNetworkReply>
#include <QVector>

#include <memory>

class QNetworkAccessManager;
class QNetworkReply;

namespace CheatSh {
namespace Internal {

class Settings;
class ProgressReport;

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
    void search(const QString& question); //!< search for new Question
    void requestNext();
    void requestPrev();

private:
    void query(); //!< do network request based on current question, index and options.
    /**
     * @brief If answer with index avaliable in cache returns true
     * and emits found signal and indexChanged signal. Otherwise
     * returns false
     * @param index Answer index.
     * @return true if Answer with index is in cache
     */
    bool tryAnswerFromCache(int index);
    /**
     * @brief Checks if prev/next answers can be requested and emits corresponding signals
     */
    void updatePrevNext();

    bool isRepliesActive() const;

    const Settings* settings_ = nullptr;
    QString question_;
    std::unique_ptr<QNetworkAccessManager> network_manager_;
    std::unique_ptr<QNetworkAccessManager> network_manager_stripped_;
    std::unique_ptr<ProgressReport> progress_report_;
    int answer_index_ = 0;
    QVector<QString> answers_cache_;    //!< Vector can be replaced with map/hash for sparse cache. It allow request for example 3rd answer immediately after 1st skipping 2nd. In that case pending network requests should be canceled or have more advanced process.
    QVector<QString> stripped_cache_;
    std::unique_ptr<QNetworkReply> reply_main_;  //!< to track request progress. See #17, #20
    std::unique_ptr<QNetworkReply> reply_stripped_; //NOTE: QNetworkReply has it's QNetworkAccessManager set as parent so it can be double memory management if QNetworkAccessManager first deletes its child objects and then unique_ptr does the same. So it MUST BE ensured that QNetworkReplys are declared AFTER QNetworkAccessManagers to be destroyed BEFORE them.
};

} // namespace Internal
} // namespace CheatSh

#endif // CHEATSH_H
