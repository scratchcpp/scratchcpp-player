#include <gtest/gtest.h>
#include <QSignalSpy>

#include "menuitemmodel.h"
#include "menumodel.h"

using namespace scratchcpp::uicomponents;

TEST(MenuItemModelTest, Constructor)
{
    MenuItemModel item1;
    MenuItemModel item2(&item1);
    ASSERT_EQ(item1.parent(), nullptr);
    ASSERT_EQ(item2.parent(), &item1);
}

TEST(MenuItemModelTest, Text)
{
    MenuItemModel item;
    QSignalSpy spy(&item, &MenuItemModel::textChanged);
    ASSERT_TRUE(item.text().isEmpty());

    item.setText("Test");
    ASSERT_EQ(item.text(), "Test");
    ASSERT_EQ(spy.count(), 1);
}

TEST(MenuItemModelTest, Submenu)
{
    MenuItemModel item;
    QSignalSpy spy(&item, &MenuItemModel::submenuChanged);
    ASSERT_EQ(item.submenu(), nullptr);

    MenuModel menu;
    item.setSubmenu(&menu);
    ASSERT_EQ(item.submenu(), &menu);
    ASSERT_EQ(spy.count(), 1);
}

TEST(MenuItemModelTest, IsSeparator)
{
    MenuItemModel item;
    QSignalSpy spy(&item, &MenuItemModel::isSeparatorChanged);
    ASSERT_FALSE(item.isSeparator());

    item.setIsSeparator(true);
    ASSERT_TRUE(item.isSeparator());
    ASSERT_EQ(spy.count(), 1);

    item.setIsSeparator(true);
    ASSERT_TRUE(item.isSeparator());
    ASSERT_EQ(spy.count(), 1);

    item.setIsSeparator(false);
    ASSERT_FALSE(item.isSeparator());
    ASSERT_EQ(spy.count(), 2);
}

TEST(MenuItemModelTest, Checkable)
{
    MenuItemModel item;
    QSignalSpy spy(&item, &MenuItemModel::checkableChanged);
    ASSERT_FALSE(item.checkable());

    item.setCheckable(true);
    ASSERT_TRUE(item.checkable());
    ASSERT_EQ(spy.count(), 1);

    item.setCheckable(true);
    ASSERT_TRUE(item.checkable());
    ASSERT_EQ(spy.count(), 1);

    item.setCheckable(false);
    ASSERT_FALSE(item.checkable());
    ASSERT_EQ(spy.count(), 2);
}

TEST(MenuItemModelTest, Checked)
{
    MenuItemModel item;
    QSignalSpy spy(&item, &MenuItemModel::checkedChanged);
    ASSERT_FALSE(item.checked());

    item.setChecked(true);
    ASSERT_TRUE(item.checked());
    ASSERT_EQ(spy.count(), 1);

    item.setChecked(true);
    ASSERT_TRUE(item.checked());
    ASSERT_EQ(spy.count(), 1);

    item.setChecked(false);
    ASSERT_FALSE(item.checked());
    ASSERT_EQ(spy.count(), 2);
}

TEST(MMenuItemModelTest, Enabled)
{
    MenuItemModel item;
    ASSERT_TRUE(item.enabled());
    QSignalSpy spy(&item, &MenuItemModel::enabledChanged);

    item.setEnabled(false);
    ASSERT_FALSE(item.enabled());
    ASSERT_EQ(spy.count(), 1);

    item.setEnabled(false);
    ASSERT_FALSE(item.enabled());
    ASSERT_EQ(spy.count(), 1);

    item.setEnabled(true);
    ASSERT_TRUE(item.enabled());
    ASSERT_EQ(spy.count(), 2);
}

TEST(MenuItemModelTest, Clicked)
{
    MenuItemModel item;
    QSignalSpy spy(&item, &MenuItemModel::clicked);
    emit item.clicked();
    ASSERT_EQ(spy.count(), 1);
}
