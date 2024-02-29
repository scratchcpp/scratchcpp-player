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
    return git_CommitSHA1();
}

int scratchcpp::AppInfo::buildYear() const
{
    return BUILD_YEAR;
}
