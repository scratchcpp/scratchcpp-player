// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQmlEngine>

#include "globalmodule.h"
#include "internal/appinfo.h"
#include "internal/filepaths.h"
#include "internal/settings.h"

using namespace scratchcpp;

std::string GlobalModule::moduleName() const
{
    return "global";
}

void GlobalModule::registerExports()
{
    m_appInfo = std::make_shared<AppInfo>();

    QQmlEngine::setObjectOwnership(m_appInfo.get(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<AppInfo>("ScratchCPP.Global", 1, 0, "AppInfo", m_appInfo.get());
    modularity::ioc()->registerExport<IAppInfo>(m_appInfo);

    modularity::ioc()->registerExport<FilePaths>(FilePaths::instance());

    m_settings = std::make_shared<Settings>();

    QQmlEngine::setObjectOwnership(m_settings.get(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<Settings>("ScratchCPP.Global", 1, 0, "Settings", m_settings.get());
    modularity::ioc()->registerExport<Settings>(m_settings);
}
