// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <vector>

namespace scratchcpp
{

namespace modularity
{

class IModuleSetup;

}

class App
{
    public:
        App();

        int run(int argc, char **argv);
        void addModule(modularity::IModuleSetup *module);

    private:
        void removeModules();

        std::vector<modularity::IModuleSetup *> m_modules;
};

} // namespace scratchcpp
