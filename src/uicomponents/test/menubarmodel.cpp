#include <gtest/gtest.h>
#include <QSignalSpy>

#include "menubarmodel.h"
#include "menumodel.h"

using namespace scratchcpp::uicomponents;

TEST(MenuBarModelTest, Constructor)
{
    MenuBarModel menuBar1;
    MenuBarModel menuBar2(&menuBar1);
    ASSERT_EQ(menuBar1.parent(), nullptr);
    ASSERT_EQ(menuBar2.parent(), &menuBar1);
}

TEST(MenuBarModelTest, Menus)
{
    MenuBarModel menuBar;
    QSignalSpy spy(&menuBar, &MenuBarModel::menusChanged);
    ASSERT_TRUE(menuBar.getMenus().isEmpty());

    MenuModel menu1;
    menuBar.addMenu(&menu1);
    ASSERT_EQ(spy.count(), 1);

    MenuModel menu2;
    menuBar.addMenu(&menu2);
    ASSERT_EQ(spy.count(), 2);

    MenuModel menu3;
    menuBar.addMenu(&menu3);
    ASSERT_EQ(spy.count(), 3);

    auto menus = menuBar.menus();
    ASSERT_EQ(menuBar.getMenus(), QList<MenuModel *>({ &menu1, &menu2, &menu3 }));
    ASSERT_EQ(menus.count(&menus), 3);
    ASSERT_EQ(menus.at(&menus, 0), &menu1);
    ASSERT_EQ(menus.at(&menus, 1), &menu2);
    ASSERT_EQ(menus.at(&menus, 2), &menu3);

    menuBar.removeMenu(&menu2);
    ASSERT_EQ(spy.count(), 4);

    menus = menuBar.menus();
    ASSERT_EQ(menuBar.getMenus(), QList<MenuModel *>({ &menu1, &menu3 }));
    ASSERT_EQ(menus.count(&menus), 2);
    ASSERT_EQ(menus.at(&menus, 0), &menu1);
    ASSERT_EQ(menus.at(&menus, 1), &menu3);

    menuBar.clear();
    ASSERT_EQ(spy.count(), 5);

    menus = menuBar.menus();
    ASSERT_TRUE(menuBar.getMenus().isEmpty());
    ASSERT_EQ(menus.count(&menus), 0);
}
