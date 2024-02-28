// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQmlEngine>

#include "uimodule.h"
#include "internal/uiengine.h"

using namespace scratchcpp::ui;

UiModule::UiModule()
{
}

std::string UiModule::moduleName() const
{
    return "ui";
}

void scratchcpp::ui::UiModule::registerExports()
{
    QQmlEngine::setObjectOwnership(UiEngine::instance().get(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<UiEngine>("ScratchCPP.Ui", 1, 0, "UiEngine", UiEngine::instance().get());
    modularity::ioc()->registerExport<IUiEngine>(UiEngine::instance());
}
