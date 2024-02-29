#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QQuickItem>

#include "dialogview.h"

using namespace scratchcpp::uicomponents;

TEST(DialogViewTest, Constructor)
{
    DialogView dialog;
    QObject object(&dialog);
    ASSERT_EQ(dialog.parent(), nullptr);
    ASSERT_EQ(object.parent(), &dialog);
}

TEST(DialogViewTest, ContentItem)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::contentItemChanged);
    ASSERT_EQ(dialog.contentItem(), nullptr);

    QQuickItem item;
    dialog.setContentItem(&item);
    ASSERT_EQ(dialog.contentItem(), &item);
    ASSERT_EQ(spy.count(), 1);
}

TEST(DialogViewTest, Visible)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::visibleChanged);
    ASSERT_FALSE(dialog.visible());

    dialog.setVisible(true);
    ASSERT_TRUE(dialog.visible());
    ASSERT_EQ(spy.count(), 1);

    dialog.setVisible(true);
    ASSERT_TRUE(dialog.visible());
    ASSERT_EQ(spy.count(), 1);

    dialog.setVisible(false);
    ASSERT_FALSE(dialog.visible());
    ASSERT_EQ(spy.count(), 2);
}

TEST(DialogViewTest, Title)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::titleChanged);
    ASSERT_TRUE(dialog.title().isEmpty());

    dialog.setTitle("test");
    ASSERT_EQ(dialog.title(), "test");
    ASSERT_EQ(spy.count(), 1);
}

TEST(DialogViewTest, Modal)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::modalChanged);
    ASSERT_TRUE(dialog.modal());

    dialog.setModal(false);
    ASSERT_FALSE(dialog.modal());
    ASSERT_EQ(spy.count(), 1);

    dialog.setModal(false);
    ASSERT_FALSE(dialog.modal());
    ASSERT_EQ(spy.count(), 1);

    dialog.setModal(true);
    ASSERT_TRUE(dialog.modal());
    ASSERT_EQ(spy.count(), 2);
}

TEST(DialogViewTest, MinimumWidth)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::minimumWidthChanged);
    ASSERT_EQ(dialog.minimumWidth(), 0);

    dialog.setMinimumWidth(45);
    ASSERT_EQ(dialog.minimumWidth(), 45);
    ASSERT_EQ(spy.count(), 1);
}

TEST(DialogViewTest, MinimumHeight)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::minimumHeightChanged);
    ASSERT_EQ(dialog.minimumHeight(), 0);

    dialog.setMinimumHeight(84);
    ASSERT_EQ(dialog.minimumHeight(), 84);
    ASSERT_EQ(spy.count(), 1);
}

TEST(DialogViewTest, MaximumWidth)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::maximumWidthChanged);
    ASSERT_EQ(dialog.maximumWidth(), QWIDGETSIZE_MAX);

    dialog.setMaximumWidth(45);
    ASSERT_EQ(dialog.maximumWidth(), 45);
    ASSERT_EQ(spy.count(), 1);
}

TEST(DialogViewTest, MaximumHeight)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::maximumHeightChanged);
    ASSERT_EQ(dialog.maximumHeight(), QWIDGETSIZE_MAX);

    dialog.setMaximumHeight(84);
    ASSERT_EQ(dialog.maximumHeight(), 84);
    ASSERT_EQ(spy.count(), 1);
}

TEST(DialogViewTest, AutoClose)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::autoCloseChanged);
    ASSERT_TRUE(dialog.autoClose());

    dialog.setAutoClose(false);
    ASSERT_FALSE(dialog.autoClose());
    ASSERT_EQ(spy.count(), 1);

    dialog.setAutoClose(false);
    ASSERT_FALSE(dialog.autoClose());
    ASSERT_EQ(spy.count(), 1);

    dialog.setAutoClose(true);
    ASSERT_TRUE(dialog.autoClose());
    ASSERT_EQ(spy.count(), 2);
}

TEST(DialogViewTest, Closable)
{
    DialogView dialog;
    QSignalSpy spy(&dialog, &DialogView::closableChanged);
    ASSERT_TRUE(dialog.closable());

    dialog.setClosable(false);
    ASSERT_FALSE(dialog.closable());
    ASSERT_EQ(spy.count(), 1);

    dialog.setClosable(false);
    ASSERT_FALSE(dialog.closable());
    ASSERT_EQ(spy.count(), 1);

    dialog.setClosable(true);
    ASSERT_TRUE(dialog.closable());
    ASSERT_EQ(spy.count(), 2);
}
