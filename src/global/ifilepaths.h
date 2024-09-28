// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QString>

#include "modularity/ioc.h"

namespace scratchcpp
{

class IFilePaths : MODULE_EXPORT_INTERFACE
{
    public:
        virtual ~IFilePaths() { }

        virtual QString configLocation() const = 0;
};

} // namespace scratchcpp
