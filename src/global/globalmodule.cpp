// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQmlEngine>

#include "globalmodule.h"
#include "internal/appinfo.h"
#include "internal/filepaths.h"

using namespace scratchcpp;

std::string GlobalModule::moduleName() const
{
    return "global";
}

void GlobalModule::registerExports()
{
    m_appInfo = std::make_shared<AppInfo>();

    QQmlEngine::setObjectOwnership(m_appInfo.get(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<AppInfo>("ScratchCPP.Ui", 1, 0, "AppInfo", m_appInfo.get());
    modularity::ioc()->registerExport<IAppInfo>(m_appInfo);

    modularity::ioc()->registerExport<FilePaths>(FilePaths::instance());
}
