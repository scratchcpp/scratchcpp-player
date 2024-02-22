// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "modularity/imodulesetup.h"

namespace scratchcpp
{

class GlobalModule : public modularity::IModuleSetup
{
    public:
        std::string moduleName() const override;
};

} // namespace scratchcpp
