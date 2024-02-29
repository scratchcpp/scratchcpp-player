// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "modularity/ioc.h"

class QString;

namespace scratchcpp
{

class IAppInfo : MODULE_EXPORT_INTERFACE
{
    public:
        virtual ~IAppInfo() { }

        virtual QString revision() const = 0;
        virtual int buildYear() const = 0;
};

} // namespace scratchcpp
