// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QVariant>
#include "modularity/ioc.h"

#define INIT_SETTINGS_KEY(keyName, defaultValue) modularity::ioc()->resolve<ISettings>()->addKey(QString::fromStdString(moduleName()), keyName, defaultValue)

namespace scratchcpp
{

class ISettings : MODULE_EXPORT_INTERFACE
{
    public:
        virtual ~ISettings() { }

        virtual void addKey(const QString &moduleName, const QString &keyName, const QVariant &defaultValue) = 0;
        virtual void setValue(const QString &moduleName, const QString &keyName, const QVariant &value) = 0;
        virtual QVariant getValue(const QString &moduleName, const QString &keyName) const = 0;
        virtual bool containsKey(const QString &moduleName, const QString &keyName) const = 0;

        virtual void freeze() = 0;
        virtual void saveChanges() = 0;
        virtual void discardChanges() = 0;
        virtual bool isFrozen() const = 0;
};

} // namespace scratchcpp
