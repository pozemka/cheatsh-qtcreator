#include "progressreport.h"

namespace CheatSh {
namespace Internal {

ProgressReport::ProgressReport()
{

}

void ProgressReport::startNew()
{
    progress_.reset();
    progress_ = std::make_unique<QFutureInterface<void>>();
    progress_->setProgressRange(0, 2);
    Core::FutureProgress* future_progress =
            Core::ProgressManager::addTask( progress_->future(),
                                            tr("Cheat.sh: Requesting cheat sheet"),
                                            CheatSh::Constants::TASK_ID_REQUEST );
    QObject::connect(future_progress, &Core::FutureProgress::canceled, this, &ProgressReport::cancelRequested);
    progress_->reportStarted();
}

void ProgressReport::increment()
{
    if(progress_) {
        progress_->setProgressValue(progress_->progressValue()+1);
        if(progress_->progressValue() == progress_->progressMaximum())
            progress_->reportFinished();
    }
}

void ProgressReport::cancel()
{
    if(progress_) {
        progress_->reportCanceled(); // It seems cancel() and reportCanceled do same thing
        progress_->reportFinished(); // reportFinished should follow reportCanceled
    }
}

} // namespace Internal
} // namespace CheatSh
