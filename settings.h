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
    bool comments_enabled = true;
    bool check_updates = true;
    QDate last_check_date;

    void save(QSettings *settings) const;
    void load(QSettings *settings);
};

bool operator ==(Settings &lhs, Settings &rhs);
bool operator !=(Settings &lhs, Settings &rhs);

}   // namespace Internal
}   // namespace CheatSh


#endif // SETTINGS_H
