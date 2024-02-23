// SPDX-License-Identifier: GPL-3.0-or-later

#include "menuitemmodel.h"

using namespace scratchcpp::uicomponents;

MenuItemModel::MenuItemModel(QObject *parent) :
    QObject(parent)
{
}

const QString &MenuItemModel::text() const
{
    return m_text;
}

void MenuItemModel::setText(const QString &newText)
{
    if (m_text == newText)
        return;

    m_text = newText;
    emit textChanged();
}

MenuModel *MenuItemModel::submenu() const
{
    return m_submenu;
}

void MenuItemModel::setSubmenu(MenuModel *newSubmenu)
{
    if (m_submenu == newSubmenu)
        return;

    m_submenu = newSubmenu;
    emit submenuChanged();
}

bool MenuItemModel::isSeparator() const
{
    return m_isSeparator;
}

void MenuItemModel::setIsSeparator(bool newIsSeparator)
{
    if (m_isSeparator == newIsSeparator)
        return;

    m_isSeparator = newIsSeparator;
    emit isSeparatorChanged();
}

bool MenuItemModel::checkable() const
{
    return m_checkable;
}

void MenuItemModel::setCheckable(bool newCheckable)
{
    if (m_checkable == newCheckable)
        return;

    m_checkable = newCheckable;
    emit checkableChanged();
}

bool MenuItemModel::checked() const
{
    return m_checked;
}

void MenuItemModel::setChecked(bool newChecked)
{
    if (m_checked == newChecked)
        return;

    m_checked = newChecked;
    emit checkedChanged();
}

bool MenuItemModel::enabled() const
{
    return m_enabled;
}

void MenuItemModel::setEnabled(bool newEnabled)
{
    if (m_enabled == newEnabled)
        return;

    m_enabled = newEnabled;
    emit enabledChanged();
}
