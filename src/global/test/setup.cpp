#include <gtest/gtest.h>

#include "globalmodule.h"

using namespace scratchcpp;

TEST(GlobalSetupTest, ModuleName)
{
    GlobalModule module;
    ASSERT_EQ(module.moduleName(), "global");
}
