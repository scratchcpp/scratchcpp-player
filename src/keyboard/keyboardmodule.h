// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <memory>

#include "modularity/imodulesetup.h"

namespace scratchcpp::keyboard
{

class KeyboardInfo;

class KeyboardModule : public modularity::IModuleSetup
{
    public:
        std::string moduleName() const override;

        void registerExports() override;

    private:
        std::shared_ptr<KeyboardInfo> m_keyboardInfo;
};

} // namespace scratchcpp::keyboard
