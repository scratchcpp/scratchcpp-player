// SPDX-License-Identifier: GPL-3.0-or-later

#include "themeengine.h"
#include "isettings.h"

using namespace scratchcpp;

static const QString MODULE = "ui";
static const QString THEME_KEY = "theme";
static const QString ACCENT_COLOR_KEY = "accentColor";

std::shared_ptr<ThemeEngine> ThemeEngine::m_instance = std::make_shared<ThemeEngine>();

std::shared_ptr<ThemeEngine> ThemeEngine::instance()
{
    return m_instance;
}

IThemeEngine::Theme ThemeEngine::theme() const
{
    return static_cast<Theme>(settings()->getValue(MODULE, THEME_KEY).toInt());
}

void ThemeEngine::setTheme(Theme newTheme)
{
    settings()->setValue(MODULE, THEME_KEY, static_cast<int>(newTheme));
    reloadTheme();
}

void ThemeEngine::reloadTheme()
{
    emit bgColorChanged();
    emit foregroundColorChanged();
    emit borderColorChanged();
    emit accentColorChanged();
    emit themeChanged();
}

void ThemeEngine::resetTheme()
{
    setTheme(Theme::DarkTheme);
}

const QColor &ThemeEngine::bgColor() const
{
    static const QColor dark = QColor(31, 30, 28);
    static const QColor light = QColor(255, 255, 255);
    return theme() == Theme::DarkTheme ? dark : light;
}

const QColor &ThemeEngine::foregroundColor() const
{
    static const QColor dark = QColor(255, 255, 255);
    static const QColor light = QColor(0, 0, 0);
    return theme() == Theme::DarkTheme ? dark : light;
}

const QColor &ThemeEngine::borderColor() const
{
    static const QColor dark = QColor(255, 255, 255, 64);
    static const QColor light = QColor(0, 0, 0, 64);
    return theme() == Theme::DarkTheme ? dark : light;
}

QColor ThemeEngine::accentColor() const
{
    return settings()->getValue(MODULE, ACCENT_COLOR_KEY).value<QColor>();
}

void ThemeEngine::setAccentColor(const QColor &newAccentColor)
{
    settings()->setValue(MODULE, ACCENT_COLOR_KEY, newAccentColor);
    emit accentColorChanged();
}
