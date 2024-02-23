// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

namespace scratchcpp::uicomponents
{

class MenuItemModel;

class MenuModel : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
        Q_PROPERTY(QQmlListProperty<MenuItemModel> items READ items NOTIFY itemsChanged)

    public:
        explicit MenuModel(QObject *parent = nullptr);

        const QString &title() const;
        void setTitle(const QString &newTitle);

        QQmlListProperty<MenuItemModel> items();
        const QList<MenuItemModel *> &getItems() const;

        void addItem(MenuItemModel *item);
        void removeItem(MenuItemModel *item);
        void clear();

    signals:
        void titleChanged();
        void itemsChanged();

    private:
        QString m_title;
        QList<MenuItemModel *> m_items;
};

} // namespace scratchcpp::uicomponents
