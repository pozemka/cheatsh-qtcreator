#include "cheatfilter.h"
#include <QDebug>

using Core::LocatorFilterEntry;

namespace CheatSh {
namespace Internal {

CheatFilter::CheatFilter()
{
    setId("cheat.sh");
    setDisplayName(tr("cheat.sh"));
    setShortcutString("ch");
    setPriority(High);
    setIncludedByDefault(false);
}

QList<LocatorFilterEntry> CheatFilter::matchesFor(QFutureInterface<LocatorFilterEntry>& future, const QString& entry)
{
    QList<LocatorFilterEntry> value;
    if (!future.isCanceled())
        if (!entry.isEmpty()) // avoid empty entry
            value.append(LocatorFilterEntry(this, entry, QVariant()));
//    QList<LocatorFilterEntry> others;

    //TODO: тоже можно поиск по истории. Или по каким-то локальным подсказкам, как в баше автодополнение у cheat.sh реализовано.
//        const Qt::CaseSensitivity entryCaseSensitivity = caseSensitivity(entry);
//        for (const QString &cmd : qAsConst(m_commandHistory)) {
//            if (future.isCanceled())
//                break;
//            if (cmd == entry) // avoid repeated entry
//                continue;
//            LocatorFilterEntry filterEntry(this, cmd, QVariant());
//            const int index = cmd.indexOf(entry, 0, entryCaseSensitivity);
//            if (index >= 0) {
//                filterEntry.highlightInfo = {index, entry.length()};
//                value.append(filterEntry);
//            } else {
//                others.append(filterEntry);
//            }
//        }
//    value.append(others);
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
