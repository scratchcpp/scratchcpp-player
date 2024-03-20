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
    QString rev = git_CommitSHA1();
    ASSERT_GE(rev.size(), 8);
    ASSERT_EQ(info.revision(), rev.first(8));
}

TEST(AppInfoTest, BuildYear)
{
    AppInfo info;
    ASSERT_EQ(info.buildYear(), BUILD_YEAR);
}
