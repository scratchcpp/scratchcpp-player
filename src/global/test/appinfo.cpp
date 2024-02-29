#include <gtest/gtest.h>
#include <QDebug>

#include "internal/appinfo.h"

// Workaround for multiple definition error
namespace scratchcpp::test
{
#include <git.h>
}

using namespace scratchcpp;
using namespace scratchcpp::test;

TEST(AppInfoTest, Revision)
{
    AppInfo info;
    ASSERT_EQ(info.revision(), git_CommitSHA1());
}

TEST(AppInfoTest, BuildYear)
{
    AppInfo info;
    ASSERT_EQ(info.buildYear(), BUILD_YEAR);
}
