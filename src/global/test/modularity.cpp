#include <gtest/gtest.h>
#include <modularity/ioc.h>

#include "mocks/moduleexportinterfacemock.h"
#include "fakeexport.h"

using namespace scratchcpp;
using namespace scratchcpp::modularity;

TEST(ModularityTest, StaticInstance)
{
    ASSERT_TRUE(ioc());
}

TEST(ModularityTest, Exports)
{
    auto mock = std::make_shared<ModuleExportInterfaceMock>();
    auto fake = std::make_shared<FakeExport>();
    ioc()->registerExport(mock);
    ioc()->registerExport(fake);
    ASSERT_EQ(ioc()->resolve<ModuleExportInterfaceMock>(), mock);
    ASSERT_EQ(ioc()->resolve<FakeExport>(), fake);
    ASSERT_EQ(ioc()->resolve<ModuleExportInterfaceMock>(), mock);
    ASSERT_NE(ioc()->resolve<ModuleExportInterfaceMock>(), std::static_pointer_cast<IModuleExportInterface>(fake));
    ASSERT_NE(ioc()->resolve<FakeExport>(), std::static_pointer_cast<IModuleExportInterface>(mock));

    auto another = std::make_shared<FakeExport>();
    ioc()->registerExport(another);
    ASSERT_EQ(ioc()->resolve<ModuleExportInterfaceMock>(), mock);
    ASSERT_EQ(ioc()->resolve<FakeExport>(), another);
}

TEST(ModularityTest, Inject)
{
    auto fake = std::make_shared<FakeExport>();
    auto dep1 = std::make_shared<FakeDependency>();
    ioc()->registerExport(fake);
    ioc()->registerExport(dep1);
    ASSERT_EQ(fake->dep(), dep1);

    auto dep2 = std::make_shared<FakeDependency>();
    fake->setdep(dep2);
    ASSERT_EQ(fake->dep(), dep2);
}
