// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQmlEngine>

#include "uimodule.h"
#include "isettings.h"
#include "internal/uiengine.h"
#include "internal/themeengine.h"

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

    QQmlEngine::setObjectOwnership(ThemeEngine::instance().get(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<ThemeEngine>("ScratchCPP.Ui", 1, 0, "ThemeEngine", ThemeEngine::instance().get());
    modularity::ioc()->registerExport<IThemeEngine>(ThemeEngine::instance());
}

void UiModule::initSettings()
{
    INIT_SETTINGS_KEY("theme", static_cast<int>(IThemeEngine::Theme::DarkTheme));
    INIT_SETTINGS_KEY("accentColor", QColor(0, 0, 0, 0)); // default accent color should be set by the application
}
