// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QColor>

#include "ithemeengine.h"

Q_MOC_INCLUDE("isettings.h")

namespace scratchcpp
{

class ISettings;

class ThemeEngine : public IThemeEngine
{
        Q_OBJECT
        INJECT(ISettings, settings)
        Q_PROPERTY(Theme theme READ theme WRITE setTheme NOTIFY themeChanged FINAL)
        Q_PROPERTY(QColor bgColor READ bgColor NOTIFY bgColorChanged FINAL)
        Q_PROPERTY(QColor borderColor READ borderColor NOTIFY borderColorChanged FINAL)
    public:
        static std::shared_ptr<ThemeEngine> instance();

        Theme theme() const override;
        void setTheme(Theme newTheme) override;
        Q_INVOKABLE void reloadTheme() override;
        Q_INVOKABLE void resetTheme() override;

        const QColor &bgColor() const override;
        const QColor &borderColor() const override;

    signals:
        void themeChanged();
        void bgColorChanged();
        void borderColorChanged();

    private:
        static std::shared_ptr<ThemeEngine> m_instance;
};

} // namespace scratchcpp
