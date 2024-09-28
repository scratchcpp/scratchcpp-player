// SPDX-License-Identifier: GPL-3.0-or-later

#include <QSettings>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDebug>

#include "settings.h"
#include "ifilepaths.h"

using namespace scratchcpp;

Settings::Settings(QObject *parent) :
    QObject(parent),
    m_mainSettingsInstance(paths()->configLocation(), QSettings::IniFormat),
    m_tmpSettingsInstance(paths()->configLocation() + ".tmp", QSettings::IniFormat)
{
    m_settingsInstance = &m_mainSettingsInstance;
}

void Settings::addKey(const QString &moduleName, const QString &keyName, const QVariant &defaultValue)
{
    m_defaults.insert({ moduleName, keyName }, defaultValue);
}

void Settings::setValue(const QString &moduleName, const QString &keyName, const QVariant &value)
{
    set(moduleName + "/" + keyName, value);
}

QVariant Settings::getValue(const QString &moduleName, const QString &keyName) const
{
    QPair<QString, QString> key(moduleName, keyName);
    QVariant defaultValue;
    auto it = m_defaults.find(key);

    if (it != m_defaults.cend())
        defaultValue = it.value();

    return get(moduleName + "/" + keyName, defaultValue);
}

bool Settings::containsKey(const QString &moduleName, const QString &keyName) const
{
    QPair<QString, QString> key(moduleName, keyName);
    return contains(moduleName + "/" + keyName);
}

/*
 * Switches to temporary settings. You can decide to saveChanges() or discardChanges() later.
 * This is useful for settings dialogs with a discard button.
 */
void Settings::freeze(void)
{
    Q_ASSERT(!m_frozen);
    m_settingsInstance = &m_tmpSettingsInstance;
    copySettings(&m_mainSettingsInstance, m_settingsInstance);
    m_frozen = true;
    emit stateChanged();
}

// Saves changes to real settings and switches back to them.
void Settings::saveChanges(void)
{
    Q_ASSERT(m_frozen);
    copySettings(m_settingsInstance, &m_mainSettingsInstance);
    m_mainSettingsInstance.sync();
    m_settingsInstance = &m_mainSettingsInstance;
    m_frozen = false;
    emit stateChanged();
    emit saved();
}

// Discards changes and switches back to real settings.
void Settings::discardChanges(void)
{
    Q_ASSERT(m_frozen);
    m_settingsInstance = &m_mainSettingsInstance;
    m_frozen = false;
    emit stateChanged();
    emit discarded();
}

bool Settings::isFrozen(void) const
{
    return m_frozen;
}

QVariant Settings::get(const QString &key, const QVariant &defaultValue) const
{
    Q_ASSERT(m_settingsInstance != nullptr);
#ifdef Q_OS_WASM
    if (m_settingsInstance->isWritable()) {
        if (!m_tempSettingsCopied)
            const_cast<Settings *>(this)->copyTempSettings();
        return m_settingsInstance->value(key, defaultValue);
    } else {
        // Use temporary settings until sandbox is initialized
        QSettings settings(paths()->configLocation(), QSettings::IniFormat);
        return settings.value(key, defaultValue);
    }
#else
    return m_settingsInstance->value(key, defaultValue);
#endif // Q_OS_WASM
}

bool Settings::contains(const QString &key) const
{
    Q_ASSERT(m_settingsInstance != nullptr);
#ifdef Q_OS_WASM
    if (m_settingsInstance->isWritable()) {
        if (!m_tempSettingsCopied)
            const_cast<Settings *>(this)->copyTempSettings();
        return m_settingsInstance->contains(key);
    } else {
        // Use temporary settings until sandbox is initialized
        QSettings settings(paths()->configLocation(), QSettings::IniFormat);
        return settings.contains(key);
    }
#else
    return m_settingsInstance->contains(key);
#endif // Q_OS_WASM
}

void Settings::set(const QString &key, const QVariant &value)
{
    Q_ASSERT(m_settingsInstance != nullptr);
#ifdef Q_OS_WASM
    if (m_settingsInstance->isWritable()) {
        if (!m_tempSettingsCopied)
            copyTempSettings();
        m_settingsInstance->setValue(key, value);
        m_settingsInstance->sync();
    } else {
        // Use temporary settings until sandbox is initialized
        QSettings settings(paths()->configLocation(), QSettings::IniFormat);
        settings.setValue(key, value);
    }
#else
    m_settingsInstance->setValue(key, value);
#endif // Q_OS_WASM
}

void Settings::copySettings(QSettings *source, QSettings *target)
{
#ifndef Q_OS_WASM
    target->clear();
#endif
    QStringList keys = source->allKeys();
    for (int i = 0; i < keys.count(); i++)
        target->setValue(keys[i], source->value(keys[i]));
}

#ifdef Q_OS_WASM
void Settings::copyTempSettings(void)
{
    QSettings settings(paths()->configLocation(), QSettings::IniFormat);
    copySettings(&settings, m_settingsInstance);
    m_settingsInstance->sync();
    m_tempSettingsCopied = true;
}
#endif // Q_OS_WASM
