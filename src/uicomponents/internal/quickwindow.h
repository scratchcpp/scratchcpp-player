// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQuickWindow>
#include <QWidget>

namespace scratchcpp::uicomponents
{

class QuickWindow : public QQuickWindow
{
        Q_OBJECT
        Q_PROPERTY(bool autoClose READ autoClose WRITE setAutoClose NOTIFY autoCloseChanged)
        Q_PROPERTY(bool closable READ closable WRITE setClosable NOTIFY closableChanged)

    public:
        explicit QuickWindow(QWindow *parent = nullptr);

        bool autoClose() const;
        void setAutoClose(bool newAutoClose);

        bool closable() const;
        void setClosable(bool newClosable);

    signals:
        void autoCloseChanged();
        void closableChanged();

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void showEvent(QShowEvent *event) override;
        void closeEvent(QCloseEvent *event) override;

    private:
        bool m_autoClose = true;
        bool m_closable = true;
        QWidget m_widget;
        QAccessibleWidget *m_accessibleWidget = nullptr;
};

} // namespace scratchcpp::uicomponents
