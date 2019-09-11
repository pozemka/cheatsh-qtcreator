#ifndef CHEATFILTER_H
#define CHEATFILTER_H

#include <coreplugin/locator/ilocatorfilter.h>
#include <coreplugin/icore.h>
#include <coreplugin/messagemanager.h>  //Можно печатать в панель вывода! Наверное надо намудрить чтобы прикидыаться curl. Но печатать с подсветкой в отдельную панель тоже прекрасно. Настраивать?

class CheatFilter : public Core::ILocatorFilter
{
    Q_OBJECT
public:
    CheatFilter();
    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future,
                                         const QString &entry) override;
    void accept(Core::LocatorFilterEntry selection,
                QString *newText, int *selectionStart, int *selectionLength) const override;

    void refresh(QFutureInterface<void> &) override {}

private:
    //
};

#endif // CHEATFILTER_H
