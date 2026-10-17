// SPDX-License-Identifier: GPL-3.0-or-later

#include <scratchcpp-render/scratchcpp-render.h>

#include "libraryinfo.h"

using namespace scratchcpp;

LibraryInfo::LibraryInfo(QObject *parent) :
    QObject(parent)
{
}

QString LibraryInfo::libscratchcppVersion() const
{
    return QString::fromStdString(scratchcpprender::libscratchcppVersion());
}

QString LibraryInfo::scratchcppRenderVersion() const
{
    return QString::fromStdString(scratchcpprender::version());
}
