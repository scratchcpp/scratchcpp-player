// SPDX-License-Identifier: GPL-3.0-or-later

#include <git.h>

#include "appinfo.h"

using namespace scratchcpp;

AppInfo::AppInfo(QObject *parent) :
    QObject(parent)
{
}

QString scratchcpp::AppInfo::revision() const
{
    QString rev = git_CommitSHA1();

    if (rev.size() >= 8)
        return rev.first(8);

    return "";
}

int scratchcpp::AppInfo::buildYear() const
{
    return BUILD_YEAR;
}
