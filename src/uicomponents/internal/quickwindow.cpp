// SPDX-License-Identifier: GPL-3.0-or-later

#include <QAccessibleWidget>

#include "quickwindow.h"

using namespace scratchcpp::uicomponents;

QuickWindow::QuickWindow(QWindow *parent) :
    QQuickWindow(parent)
{
    m_accessibleWidget = new QAccessibleWidget(&m_widget, QAccessible::Dialog);
    m_accessibleWidget->setText(QAccessible::Name, title());
    m_widget.setAccessibleName(title());
    QAccessibleEvent accessibleEvent(m_accessibleWidget, QAccessible::NameChanged);
    QAccessible::updateAccessibility(&accessibleEvent);

    connect(this, &QQuickWindow::windowTitleChanged, [this](const QString &title) {
        m_accessibleWidget->setText(QAccessible::Name, title);
        m_widget.setAccessibleName(title);
        QAccessibleEvent accessibleEvent(m_accessibleWidget, QAccessible::NameChanged);
        QAccessible::updateAccessibility(&accessibleEvent);
    });
}

void QuickWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && m_autoClose && m_closable)
        close();

    QQuickWindow::keyPressEvent(event);
}

void QuickWindow::showEvent(QShowEvent *event)
{
    QQuickWindow::showEvent(event);
    QAccessibleEvent accessibleEvent(m_accessibleWidget, QAccessible::Focus);
    QAccessible::updateAccessibility(&accessibleEvent);
}

void QuickWindow::closeEvent(QCloseEvent *event)
{
    if (m_closable)
        QQuickWindow::closeEvent(event);
    else
        event->ignore();
}

void QuickWindow::setAutoClose(bool newAutoClose)
{
    if (m_autoClose == newAutoClose)
        return;

    m_autoClose = newAutoClose;
    emit autoCloseChanged();
}

bool QuickWindow::closable() const
{
    return m_closable;
}

void QuickWindow::setClosable(bool newClosable)
{
    if (m_closable == newClosable)
        return;

    m_closable = newClosable;
    emit closableChanged();
}

bool QuickWindow::autoClose() const
{
    return m_autoClose;
}
