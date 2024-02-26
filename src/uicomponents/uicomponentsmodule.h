// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "modularity/imodulesetup.h"

namespace scratchcpp::uicomponents
{

class UiComponentsModule : public modularity::IModuleSetup
{
    public:
        UiComponentsModule();

        std::string moduleName() const override;
};

} // namespace scratchcpp::uicomponents
