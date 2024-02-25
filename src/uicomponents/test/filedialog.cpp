#include <gtest/gtest.h>

#include "filedialog.h"

using namespace scratchcpp::uicomponents;

TEST(FileDialogTest, Constructor)
{
    FileDialog dialog1;
    FileDialog dialog2(&dialog1);
    ASSERT_EQ(dialog1.parent(), nullptr);
    ASSERT_EQ(dialog2.parent(), &dialog1);
}

TEST(FileDialogTest, NameFilters)
{
    FileDialog dialog;
    ASSERT_TRUE(dialog.nameFilters().isEmpty());

    QStringList filters({ "a", "b", "c" });
    dialog.setNameFilters(filters);
    ASSERT_EQ(dialog.nameFilters(), filters);
}

TEST(FileDialogTest, ShowAllFiles)
{
    FileDialog dialog;
    ASSERT_TRUE(dialog.showAllFiles());

    dialog.setShowAllFiles(false);
    ASSERT_FALSE(dialog.showAllFiles());

    dialog.setShowAllFiles(false);
    ASSERT_FALSE(dialog.showAllFiles());

    dialog.setShowAllFiles(true);
    ASSERT_TRUE(dialog.showAllFiles());
}

TEST(FileDialogTest, DefaultSuffix)
{
    FileDialog dialog;
    ASSERT_TRUE(dialog.defaultSuffix().isEmpty());

    dialog.setDefaultSuffix(".txt");
    ASSERT_EQ(dialog.defaultSuffix(), ".txt");
}
