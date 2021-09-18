#include "cheatfilter.h"

#include "settings.h"
#include "cheatshconstants.h"

#include <QDebug>
#include <QMutex>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QThread>
#include <QWaitCondition>

using Core::LocatorFilterEntry;

namespace CheatSh {
namespace Internal {

CheatFilter::CheatFilter(const Settings* settigns) :
    settings_(settigns)
{
    setId("cheat.sh");
    setDisplayName(tr("Search cheat.sh"));  // Text in Locator
    setShortcutString("ch");
    setPriority(High);
    setIncludedByDefault(false);
}

CheatFilter::~CheatFilter()
{
}

QList<LocatorFilterEntry> CheatFilter::matchesFor(QFutureInterface<LocatorFilterEntry>& future,
                                                  const QString& entry)
{
    QList<LocatorFilterEntry> value;
    if (!future.isCanceled())
        if (!entry.isEmpty()) // avoid empty entry
            value.append(LocatorFilterEntry(this, entry, QVariant()));

    return value;
}

void CheatFilter::accept(Core::LocatorFilterEntry selection, QString* newText, int* selectionStart, int* selectionLength) const
{
    Q_UNUSED(selection)
    Q_UNUSED(newText)
    Q_UNUSED(selectionStart)
    Q_UNUSED(selectionLength)
//    qDebug() << "accept" << selection.displayName << *newText << *selectionStart << *selectionLength;   //accept "aaa" "" -1 0
    if(!selection.displayName.isEmpty())
        emit query(selection.displayName);
}

}}
