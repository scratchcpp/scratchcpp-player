#pragma once

#include <modularity/imodulesetup.h>
#include <gmock/gmock.h>

namespace scratchcpp::modularity
{

class ModuleSetupMock : public IModuleSetup
{
    public:
        MOCK_METHOD(std::string, moduleName, (), (const, override));

        MOCK_METHOD(void, registerExports, (), (override));
        MOCK_METHOD(void, initSettings, (), (override));

        MOCK_METHOD(void, onPreInit, (), (override));
        MOCK_METHOD(void, onInit, (), (override));
        MOCK_METHOD(void, onDeinit, (), (override));
        MOCK_METHOD(void, onDestroy, (), (override));

        MOCK_METHOD(void, onStartApp, (), (override));
};

} // namespace scratchcpp::modularity
