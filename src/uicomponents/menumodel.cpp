// SPDX-License-Identifier: GPL-3.0-or-later

#include "menumodel.h"

using namespace scratchcpp::uicomponents;

MenuModel::MenuModel(QObject *parent) :
    QObject(parent)
{
}

const QString &MenuModel::title() const
{
    return m_title;
}

void MenuModel::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;

    m_title = newTitle;
    emit titleChanged();
}

QQmlListProperty<MenuItemModel> MenuModel::items()
{
    return QQmlListProperty<MenuItemModel>(this, &m_items);
}

const QList<MenuItemModel *> &MenuModel::getItems() const
{
    return m_items;
}

void MenuModel::addItem(MenuItemModel *item)
{
    m_items.push_back(item);
    emit itemsChanged();
}

void MenuModel::removeItem(MenuItemModel *item)
{
    m_items.erase(std::remove(m_items.begin(), m_items.end(), item), m_items.end());
    emit itemsChanged();
}

void MenuModel::clear()
{
    m_items.clear();
    emit itemsChanged();
}
