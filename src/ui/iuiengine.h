// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QDialogButtonBox>

#include "modularity/ioc.h"

class QQmlEngine;

namespace scratchcpp::ui
{

class IUiEngine : MODULE_EXPORT_INTERFACE
{
    public:
        virtual ~IUiEngine() { }

        virtual QQmlEngine *qmlEngine() const = 0;

        virtual QString standardButtonText(QDialogButtonBox::StandardButton button) const = 0;
};

} // namespace scratchcpp::ui
