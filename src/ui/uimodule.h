// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "modularity/imodulesetup.h"

namespace scratchcpp::ui
{

class UiModule : public modularity::IModuleSetup
{
    public:
        UiModule();

        std::string moduleName() const override;
};

} // namespace scratchcpp::ui
