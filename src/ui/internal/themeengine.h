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
        Q_PROPERTY(QColor foregroundColor READ foregroundColor NOTIFY foregroundColorChanged FINAL)
        Q_PROPERTY(QColor borderColor READ borderColor NOTIFY borderColorChanged FINAL)
        Q_PROPERTY(QColor accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged FINAL)
    public:
        static std::shared_ptr<ThemeEngine> instance();

        Theme theme() const override;
        void setTheme(Theme newTheme) override;
        Q_INVOKABLE void reloadTheme() override;
        Q_INVOKABLE void resetTheme() override;

        const QColor &bgColor() const override;
        const QColor &foregroundColor() const override;
        const QColor &borderColor() const override;

        QColor accentColor() const override;
        void setAccentColor(const QColor &newAccentColor) override;

    signals:
        void themeChanged();
        void bgColorChanged();
        void foregroundColorChanged();
        void borderColorChanged();
        void accentColorChanged();

    private:
        static std::shared_ptr<ThemeEngine> m_instance;
};

} // namespace scratchcpp
