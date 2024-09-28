// SPDX-License-Identifier: GPL-3.0-or-later

#include <QStandardPaths>
#include <QCoreApplication>

#include "filepaths.h"

using namespace scratchcpp;

std::shared_ptr<FilePaths> FilePaths::m_instance = std::make_shared<FilePaths>();

std::shared_ptr<FilePaths> FilePaths::instance()
{
    return m_instance;
}

QString scratchcpp::FilePaths::configLocation() const
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/" + qApp->applicationName() + "/config.ini";
}
