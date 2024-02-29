// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "internal/quickwindow.h"

Q_MOC_INCLUDE(<QQuickItem>)

namespace scratchcpp::uicomponents
{

class DialogView : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        Q_PROPERTY(QQuickItem *contentItem READ contentItem WRITE setContentItem NOTIFY contentItemChanged)
        Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
        Q_PROPERTY(bool modal READ modal WRITE setModal NOTIFY modalChanged)
        Q_PROPERTY(int minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumWidthChanged)
        Q_PROPERTY(int minimumHeight READ minimumHeight WRITE setMinimumHeight NOTIFY minimumHeightChanged)
        Q_PROPERTY(int maximumWidth READ maximumWidth WRITE setMaximumWidth NOTIFY maximumWidthChanged)
        Q_PROPERTY(int maximumHeight READ maximumHeight WRITE setMaximumHeight NOTIFY maximumHeightChanged)
        Q_PROPERTY(bool autoClose READ autoClose WRITE setAutoClose NOTIFY autoCloseChanged)
        Q_PROPERTY(bool closable READ closable WRITE setClosable NOTIFY closableChanged)
        Q_PROPERTY(QQuickItem *activeFocusItem READ activeFocusItem NOTIFY activeFocusItemChanged)

    public:
        explicit DialogView(QObject *parent = nullptr);

        QQuickItem *contentItem() const;
        void setContentItem(QQuickItem *newContentItem);

        bool visible() const;
        void setVisible(bool newVisible);

        QString title() const;
        void setTitle(const QString &newTitle);

        bool modal() const;
        void setModal(bool newModal);

        int minimumWidth() const;
        void setMinimumWidth(int newMinimumWidth);

        int minimumHeight() const;
        void setMinimumHeight(int newMinimumHeight);

        int maximumWidth() const;
        void setMaximumWidth(int newMaximumWidth);

        int maximumHeight() const;
        void setMaximumHeight(int newMaximumHeight);

        Q_INVOKABLE void setMaximizedState();
        Q_INVOKABLE void setNormalState();
        Q_INVOKABLE void showMaximized();
        Q_INVOKABLE void showNormal();

        bool autoClose() const;
        void setAutoClose(bool newAutoClose);

        bool closable() const;
        void setClosable(bool newClosable);

        QQuickItem *activeFocusItem() const;

    signals:
        void contentItemChanged();
        void visibleChanged();
        void titleChanged();
        void modalChanged();
        void minimumWidthChanged();
        void minimumHeightChanged();
        void maximumWidthChanged();
        void maximumHeightChanged();
        void autoCloseChanged();
        void closableChanged();
        void activeFocusItemChanged();

    private:
        QuickWindow m_window;
        QQuickItem *m_contentItem = nullptr;
        bool m_modal = true;
};

} // namespace scratchcpp::uicomponents
