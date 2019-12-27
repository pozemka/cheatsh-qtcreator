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

    settings->endGroup();
    settings->sync();
}

void Settings::load(QSettings* settings)
{
    settings->beginGroup((Constants::SETTINGS_GROUP));

    context = settings->value(Constants::CHT_CONTEXT, Constants::CHT_DEFAULT_CONTEXT).toString();
    url = settings->value(Constants::CHT_URL, Constants::CHT_DEFAULT_URL).toUrl();
    comments_enabled = settings->value(Constants::CHT_COMMENTS, true).toBool();

    settings->endGroup();
}

bool operator ==(Settings& lhs, Settings& rhs)
{
    return std::tie(lhs.context, lhs.url, lhs.comments_enabled) ==
           std::tie(rhs.context, rhs.url, rhs.comments_enabled);
}

bool operator !=(Settings& lhs, Settings& rhs)
{
    return ! operator==(lhs, rhs);
}


}   // namespace Internal
}   // namespace CheatSh
