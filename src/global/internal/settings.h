// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>
#include <QSettings>

#include "isettings.h"
#include "ifilepaths.h"

class QSettings;

namespace scratchcpp
{

// class IFilePaths;

class Settings
    : public QObject
    , public ISettings
{
        Q_OBJECT
        INJECT(IFilePaths, paths)
    public:
        Settings(QObject *parent = nullptr);

        void addKey(const QString &moduleName, const QString &keyName, const QVariant &defaultValue) override;
        Q_INVOKABLE void setValue(const QString &moduleName, const QString &keyName, const QVariant &value) override;
        Q_INVOKABLE QVariant getValue(const QString &moduleName, const QString &keyName) const override;
        Q_INVOKABLE bool containsKey(const QString &moduleName, const QString &keyName) const override;
        Q_INVOKABLE void freeze(void) override;
        Q_INVOKABLE void saveChanges(void) override;
        Q_INVOKABLE void discardChanges(void) override;
        Q_INVOKABLE bool isFrozen(void) const override;

    signals:
        void stateChanged();
        void saved();
        void discarded();

    private:
        QVariant get(const QString &key, const QVariant &defaultValue) const;
        bool contains(const QString &key) const;
        void set(const QString &key, const QVariant &value);

        static void copySettings(QSettings *source, QSettings *target);

        QSettings *m_settingsInstance = nullptr;
        QSettings m_mainSettingsInstance;
        QSettings m_tmpSettingsInstance;
        bool m_frozen = false;
        QMap<QPair<QString, QString>, QVariant> m_defaults;

#ifdef Q_OS_WASM
        bool m_tempSettingsCopied = false;
        void copyTempSettings(void);
#endif // Q_OS_WASM
};

} // namespace scratchcpp
