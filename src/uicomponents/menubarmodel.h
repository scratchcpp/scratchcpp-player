// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

Q_MOC_INCLUDE("menumodel.h")

namespace scratchcpp::uicomponents
{

class MenuModel;

class MenuBarModel : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        Q_PROPERTY(QQmlListProperty<MenuModel> menus READ menus NOTIFY menusChanged)

    public:
        explicit MenuBarModel(QObject *parent = nullptr);

        QQmlListProperty<MenuModel> menus();
        const QList<MenuModel *> &getMenus() const;

        void addMenu(MenuModel *menu);
        void removeMenu(MenuModel *menu);
        void clear();

    signals:
        void menusChanged();

    private:
        QList<MenuModel *> m_menus;
};

} // namespace scratchcpp::uicomponents
