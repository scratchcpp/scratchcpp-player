#include <gtest/gtest.h>
#include <QSignalSpy>

#include "menumodel.h"
#include "menuitemmodel.h"

using namespace scratchcpp::uicomponents;

TEST(MenuModelTest, Constructor)
{
    MenuModel menu1;
    MenuModel menu2(&menu1);
    ASSERT_EQ(menu1.parent(), nullptr);
    ASSERT_EQ(menu2.parent(), &menu1);
}

TEST(MenuModelTest, Title)
{
    MenuModel menu;
    QSignalSpy spy(&menu, &MenuModel::titleChanged);
    ASSERT_TRUE(menu.title().isEmpty());

    menu.setTitle("Test");
    ASSERT_EQ(menu.title(), "Test");
    ASSERT_EQ(spy.count(), 1);
}

TEST(MenuModelTest, Items)
{
    MenuModel menu;
    QSignalSpy spy(&menu, &MenuModel::itemsChanged);
    ASSERT_TRUE(menu.getItems().isEmpty());

    MenuItemModel item1;
    menu.addItem(&item1);
    ASSERT_EQ(spy.count(), 1);

    MenuItemModel item2;
    menu.addItem(&item2);
    ASSERT_EQ(spy.count(), 2);

    MenuItemModel item3;
    menu.addItem(&item3);
    ASSERT_EQ(spy.count(), 3);

    auto items = menu.items();
    ASSERT_EQ(menu.getItems(), QList<MenuItemModel *>({ &item1, &item2, &item3 }));
    ASSERT_EQ(items.count(&items), 3);
    ASSERT_EQ(items.at(&items, 0), &item1);
    ASSERT_EQ(items.at(&items, 1), &item2);
    ASSERT_EQ(items.at(&items, 2), &item3);

    menu.removeItem(&item2);
    ASSERT_EQ(spy.count(), 4);

    items = menu.items();
    ASSERT_EQ(menu.getItems(), QList<MenuItemModel *>({ &item1, &item3 }));
    ASSERT_EQ(items.count(&items), 2);
    ASSERT_EQ(items.at(&items, 0), &item1);
    ASSERT_EQ(items.at(&items, 1), &item3);

    menu.clear();
    ASSERT_EQ(spy.count(), 5);

    items = menu.items();
    ASSERT_TRUE(menu.getItems().isEmpty());
    ASSERT_EQ(items.count(&items), 0);
}
