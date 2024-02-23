// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "modulesioc.h"

#define INJECT(Interface, getter)                                                                                                                                                                      \
private:                                                                                                                                                                                               \
    static inline std::shared_ptr<Interface> _##getter = nullptr;                                                                                                                                      \
                                                                                                                                                                                                       \
public:                                                                                                                                                                                                \
    static std::shared_ptr<Interface> getter()                                                                                                                                                         \
    {                                                                                                                                                                                                  \
        if (!_##getter) {                                                                                                                                                                              \
            _##getter = modularity::ioc()->resolve<Interface>();                                                                                                                                       \
        }                                                                                                                                                                                              \
        return _##getter;                                                                                                                                                                              \
    }                                                                                                                                                                                                  \
    static void set##getter(std::shared_ptr<Interface> impl)                                                                                                                                           \
    {                                                                                                                                                                                                  \
        _##getter = impl;                                                                                                                                                                              \
    }

namespace scratchcpp::modularity
{

inline ModulesIoC *ioc()
{
    return ModulesIoC::instance();
}

} // namespace scratchcpp::modularity
