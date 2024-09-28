// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>

#include "modularity/ioc.h"

namespace scratchcpp
{

class IThemeEngine
    : public QObject
    , MODULE_EXPORT_INTERFACE
{
        Q_OBJECT
    public:
        virtual ~IThemeEngine() { }

        enum class Theme
        {
            LightTheme = 1,
            DarkTheme = 0
        };
        Q_ENUM(Theme)

        virtual Theme theme() const = 0;
        virtual void setTheme(Theme newTheme) = 0;
        virtual void reloadTheme() = 0;
        virtual void resetTheme() = 0;

        virtual const QColor &bgColor() const = 0;
        virtual const QColor &foregroundColor() const = 0;
        virtual const QColor &borderColor() const = 0;
};

} // namespace scratchcpp
