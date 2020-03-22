#ifndef PROGRESSREPORT_H
#define PROGRESSREPORT_H

#include "cheatshconstants.h"

#include <coreplugin/progressmanager/futureprogress.h>
#include <coreplugin/progressmanager/progressmanager.h>

#include <QObject>

#include <memory>


namespace CheatSh {
namespace Internal {

/**
 * @brief The ProgressReport class is a basic progress report wrapper
 */
class ProgressReport : public QObject
{
    Q_OBJECT
public:
    ProgressReport();

    void startNew();
    void increment();
    void cancel();

signals:
    void cancelRequested();

private:
    std::unique_ptr<QFutureInterface<void>> progress_;
};

} // namespace Internal
} // namespace CheatSh

#endif // PROGRESSREPORT_H
