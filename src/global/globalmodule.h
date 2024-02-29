// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <memory>

#include "modularity/imodulesetup.h"

namespace scratchcpp
{

class AppInfo;

class GlobalModule : public modularity::IModuleSetup
{
    public:
        std::string moduleName() const override;

        void registerExports() override;

    private:
        std::shared_ptr<AppInfo> m_appInfo;
};

} // namespace scratchcpp
