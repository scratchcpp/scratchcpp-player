// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>

#include "iappinfo.h"

namespace scratchcpp
{

class AppInfo
    : public QObject
    , public IAppInfo
{
        Q_OBJECT
    public:
        explicit AppInfo(QObject *parent = nullptr);

        Q_INVOKABLE QString revision() const override;
        Q_INVOKABLE int buildYear() const override;
};

} // namespace scratchcpp
