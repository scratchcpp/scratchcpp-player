// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <modularity/ioc.h>
#include <Qt>

namespace scratchcpp::keyboard
{

class IKeyboardInfo : MODULE_EXPORT_INTERFACE
{
    public:
        virtual ~IKeyboardInfo() { }

        virtual Qt::KeyboardModifiers keyboardModifiers() const = 0;
};

} // namespace scratchcpp::keyboard
