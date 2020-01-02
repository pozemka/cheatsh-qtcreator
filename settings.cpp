#include "settings.h"

#include "cheatshconstants.h"
#include <QDebug>

#include <QSettings>

#include <tuple>

namespace CheatSh {
namespace Internal {

void Settings::save(QSettings* settings) const
{
    settings->beginGroup((Constants::SETTINGS_GROUP));

    settings->setValue(Constants::CHT_CONTEXT, context);
    settings->setValue(Constants::CHT_URL, url);
    settings->setValue(Constants::CHT_COMMENTS, comments_enabled);
    settings->setValue(Constants::CHT_CHECK_UPDATES, check_updates);
    settings->setValue(Constants::CHT_LAST_CHECK_DATE, last_check_date);

    settings->endGroup();
    settings->sync();
}

void Settings::load(QSettings* settings)
{
    settings->beginGroup((Constants::SETTINGS_GROUP));

    context = settings->value(Constants::CHT_CONTEXT, Constants::CHT_DEFAULT_CONTEXT).toString();
    url = settings->value(Constants::CHT_URL, Constants::CHT_DEFAULT_URL).toUrl();
    comments_enabled = settings->value(Constants::CHT_COMMENTS, true).toBool();
    check_updates = settings->value(Constants::CHT_CHECK_UPDATES, true).toBool();
    last_check_date = settings->value(Constants::CHT_LAST_CHECK_DATE, QDate(2000, 1, 1)).toDate();

    settings->endGroup();
}

bool operator ==(Settings& lhs, Settings& rhs)
{
    return std::tie(lhs.context, lhs.url, lhs.comments_enabled, lhs.check_updates, lhs.last_check_date) ==
           std::tie(rhs.context, rhs.url, rhs.comments_enabled, rhs.check_updates, rhs.last_check_date);
}

bool operator !=(Settings& lhs, Settings& rhs)
{
    return ! operator==(lhs, rhs);
}


}   // namespace Internal
}   // namespace CheatSh
