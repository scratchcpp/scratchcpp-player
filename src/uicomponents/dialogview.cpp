// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQuickItem>

#include "dialogview.h"

using namespace scratchcpp::uicomponents;

DialogView::DialogView(QObject *parent) :
    QObject(parent)
{
    if (m_modal)
        m_window.setModality(Qt::ApplicationModal);
    else
        m_window.setModality(Qt::NonModal);

    m_window.setFlags(m_window.flags() | Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    connect(&m_window, &QQuickWindow::visibleChanged, this, &DialogView::visibleChanged);
    connect(&m_window, &QQuickWindow::windowTitleChanged, this, &DialogView::titleChanged);
    connect(&m_window, &QQuickWindow::minimumWidthChanged, this, &DialogView::minimumWidthChanged);
    connect(&m_window, &QQuickWindow::minimumHeightChanged, this, &DialogView::minimumHeightChanged);
    connect(&m_window, &QQuickWindow::maximumWidthChanged, this, &DialogView::maximumWidthChanged);
    connect(&m_window, &QQuickWindow::maximumHeightChanged, this, &DialogView::maximumHeightChanged);
    connect(&m_window, &QuickWindow::autoCloseChanged, this, &DialogView::autoCloseChanged);
    connect(&m_window, &QuickWindow::closableChanged, this, &DialogView::closableChanged);
    connect(&m_window, &QQuickWindow::activeFocusItemChanged, this, &DialogView::activeFocusItemChanged);
}

QQuickItem *DialogView::contentItem() const
{
    return m_contentItem;
}

void DialogView::setContentItem(QQuickItem *newContentItem)
{
    if (m_contentItem == newContentItem)
        return;

    m_contentItem = newContentItem;
    m_contentItem->setParentItem(m_window.contentItem());
    emit contentItemChanged();
}

bool DialogView::visible() const
{
    return m_window.isVisible();
}

void DialogView::setVisible(bool newVisible)
{
    m_window.setVisible(newVisible);
}

QString DialogView::title() const
{
    return m_window.title();
}

void DialogView::setTitle(const QString &newTitle)
{
    m_window.setTitle(newTitle);
}

bool DialogView::modal() const
{
    return m_modal;
}

void DialogView::setModal(bool newModal)
{
    if (m_modal == newModal)
        return;

    m_modal = newModal;

    if (m_modal)
        m_window.setModality(Qt::ApplicationModal);
    else
        m_window.setModality(Qt::NonModal);

    emit modalChanged();
}

int DialogView::minimumWidth() const
{
    return m_window.minimumWidth();
}

void DialogView::setMinimumWidth(int newMinimumWidth)
{
    m_window.setMinimumWidth(newMinimumWidth);
}

int DialogView::minimumHeight() const
{
    return m_window.minimumHeight();
}

void DialogView::setMinimumHeight(int newMinimumHeight)
{
    m_window.setMinimumHeight(newMinimumHeight);
}

int DialogView::maximumWidth() const
{
    return m_window.maximumWidth();
}

void DialogView::setMaximumWidth(int newMaximumWidth)
{
    m_window.setMaximumWidth(newMaximumWidth);
}

int DialogView::maximumHeight() const
{
    return m_window.maximumHeight();
}

void DialogView::setMaximumHeight(int newMaximumHeight)
{
    m_window.setMaximumHeight(newMaximumHeight);
}

void DialogView::setMaximizedState()
{
    m_window.setWindowStates(Qt::WindowMaximized);
}

void DialogView::setNormalState()
{
    m_window.setWindowState(Qt::WindowNoState);
}

void DialogView::showMaximized()
{
    m_window.showMaximized();
}

void DialogView::showNormal()
{
    m_window.showNormal();
}

bool DialogView::autoClose() const
{
    return m_window.autoClose();
}

void DialogView::setAutoClose(bool newAutoClose)
{
    m_window.setAutoClose(newAutoClose);
}

bool DialogView::closable() const
{
    return m_window.closable();
}

void DialogView::setClosable(bool newClosable)
{
    m_window.setClosable(newClosable);
}

QQuickItem *DialogView::activeFocusItem() const
{
    return m_window.activeFocusItem();
}
