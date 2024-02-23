// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

Q_MOC_INCLUDE("uicomponents/menubarmodel.h")

namespace scratchcpp
{

namespace uicomponents
{

class MenuBarModel;

}

class AppMenuBar : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON
        Q_PROPERTY(uicomponents::MenuBarModel *model READ model NOTIFY modelChanged)

    public:
        explicit AppMenuBar(QObject *parent = nullptr);

        uicomponents::MenuBarModel *model() const;

    signals:
        void modelChanged();

    private:
        uicomponents::MenuBarModel *m_model = nullptr;
};

} // namespace scratchcpp
