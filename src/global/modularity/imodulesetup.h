// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string>

namespace scratchcpp::modularity
{

class IModuleSetup
{
    public:
        virtual ~IModuleSetup() { }

        virtual std::string moduleName() const = 0;

        virtual void registerExports() { }
        virtual void initSettings() { }

        virtual void onPreInit() { }
        virtual void onInit() { }
        virtual void onDeinit() { }
        virtual void onDestroy() { }

        virtual void onStartApp() { }
};

} // namespace scratchcpp::modularity
