#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDate>
#include <QString>
#include <QUrl>

class QSettings;

namespace CheatSh {
namespace Internal {

class Settings
{
public:
    QString context;
    QUrl url;
    bool comments_enabled;
    bool check_updates;
    QDate last_check_date;

    void save(QSettings *settings) const;
    void load(QSettings *settings);
};

bool operator ==(Settings &s1, Settings &s2);
bool operator !=(Settings &s1, Settings &s2);

}   // namespace Internal
}   // namespace CheatSh


#endif // SETTINGS_H
