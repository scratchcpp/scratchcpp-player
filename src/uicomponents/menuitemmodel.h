// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

namespace scratchcpp::uicomponents
{

class MenuModel;

class MenuItemModel : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
        Q_PROPERTY(MenuModel *submenu READ submenu WRITE setSubmenu NOTIFY submenuChanged)
        Q_PROPERTY(bool isSeparator READ isSeparator WRITE setIsSeparator NOTIFY isSeparatorChanged)
        Q_PROPERTY(bool checkable READ checkable WRITE setCheckable NOTIFY checkableChanged)
        Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    public:
        explicit MenuItemModel(QObject *parent = nullptr);

        const QString &text() const;
        void setText(const QString &newText);

        MenuModel *submenu() const;
        void setSubmenu(MenuModel *newSubmenu);

        bool isSeparator() const;
        void setIsSeparator(bool newIsSeparator);

        bool checkable() const;
        void setCheckable(bool newCheckable);

        bool checked() const;
        void setChecked(bool newChecked);

        bool enabled() const;
        void setEnabled(bool newEnabled);

    signals:
        void textChanged();
        void submenuChanged();
        void isSeparatorChanged();
        void checkableChanged();
        void checkedChanged();
        void enabledChanged();
        void clicked();

    private:
        QString m_text;
        MenuModel *m_submenu = nullptr;
        bool m_isSeparator = false;
        bool m_checkable = false;
        bool m_checked = false;
        bool m_enabled = true;
};

} // namespace scratchcpp::uicomponents
