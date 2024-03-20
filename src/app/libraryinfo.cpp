// SPDX-License-Identifier: GPL-3.0-or-later

#include <scratchcpp/scratchconfiguration.h>
#include <scratchcpp-render/scratchcpp-render.h>

#include "libraryinfo.h"

using namespace scratchcpp;

LibraryInfo::LibraryInfo(QObject *parent) :
    QObject(parent)
{
}

QString LibraryInfo::libscratchcppVersion() const
{
    return QString::fromStdString(libscratchcpp::ScratchConfiguration::version());
}

QString LibraryInfo::scratchcppRenderVersion() const
{
    return QString::fromStdString(scratchcpprender::version());
}
