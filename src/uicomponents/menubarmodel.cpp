// SPDX-License-Identifier: GPL-3.0-or-later

#include "menubarmodel.h"

using namespace scratchcpp::uicomponents;

MenuBarModel::MenuBarModel(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<MenuModel> MenuBarModel::menus()
{
    return QQmlListProperty<MenuModel>(this, &m_menus);
}

const QList<MenuModel *> &MenuBarModel::getMenus() const
{
    return m_menus;
}

void MenuBarModel::addMenu(MenuModel *menu)
{
    m_menus.push_back(menu);
    emit menusChanged();
}

void MenuBarModel::removeMenu(MenuModel *menu)
{
    m_menus.erase(std::remove(m_menus.begin(), m_menus.end(), menu), m_menus.end());
    emit menusChanged();
}

void MenuBarModel::clear()
{
    m_menus.clear();
    emit menusChanged();
}
