// SPDX-License-Identifier: GPL-3.0-or-later

#include <QCoreApplication>
#include <QPushButton>
#ifdef Q_OS_LINUX
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#endif

#include "uiengine.h"

using namespace scratchcpp::ui;

std::shared_ptr<UiEngine> UiEngine::m_instance = std::make_shared<UiEngine>();

UiEngine::UiEngine(QObject *parent) :
    QObject(parent)
{
}

UiEngine::~UiEngine()
{
    if (m_dialogButtonBox)
        m_dialogButtonBox->deleteLater();
}

std::shared_ptr<UiEngine> UiEngine::instance()
{
    return m_instance;
}

QQmlEngine *UiEngine::qmlEngine() const
{
    return m_qmlEngine;
}

void UiEngine::setQmlEngine(QQmlEngine *engine)
{
    m_qmlEngine = engine;
}

QString UiEngine::standardButtonText(QDialogButtonBox::StandardButton button) const
{
    if (!m_dialogButtonBox)
        m_dialogButtonBox = new QDialogButtonBox; // construct on first use because widgets need QApplication

    QPushButton *btn = m_dialogButtonBox->button(button);

    if (!btn) {
        m_dialogButtonBox->addButton(button);
        btn = m_dialogButtonBox->button(button);
    }

    if (btn)
        return btn->text();
    else
        return QString();
}

QQuickItem *UiEngine::activeFocusItem() const
{
    return m_activeFocusItem;
}

void UiEngine::setActiveFocusItem(QQuickItem *newActiveFocusItem)
{
    if (m_activeFocusItem == newActiveFocusItem)
        return;

    m_activeFocusItem = newActiveFocusItem;
    emit activeFocusItemChanged();
}

bool UiEngine::useNativeMenuBar() const
{
#if defined(Q_OS_MACOS)
#if QT_VERSION < QT_VERSION_CHECK(6, 8, 0)
    return true;
#else
    // Since Qt 6.8, Qt Quick Controls menu bar is native
    return false;
#endif
#elif defined(Q_OS_LINUX)
    const QDBusConnection connection = QDBusConnection::sessionBus();
    static const QString registrarService = QStringLiteral("com.canonical.AppMenu.Registrar");
    if (const auto iface = connection.interface())
        return iface->isServiceRegistered(registrarService);
    else
        return false;
#else
    return false;
#endif
}
