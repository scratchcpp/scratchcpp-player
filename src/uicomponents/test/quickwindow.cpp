#include <gtest/gtest.h>
#include <QSignalSpy>

#include "internal/quickwindow.h"

using namespace scratchcpp::uicomponents;

TEST(QuickWindowTest, Constructor)
{
    QuickWindow window1;
    QWindow window2(&window1);
    ASSERT_EQ(window1.parent(), nullptr);
    ASSERT_EQ(window2.parent(), &window1);
}

TEST(QuickWindowTest, AutoClose)
{
    QuickWindow window;
    QSignalSpy spy(&window, &QuickWindow::autoCloseChanged);
    ASSERT_TRUE(window.autoClose());

    window.setAutoClose(false);
    ASSERT_FALSE(window.autoClose());
    ASSERT_EQ(spy.count(), 1);

    window.setAutoClose(false);
    ASSERT_FALSE(window.autoClose());
    ASSERT_EQ(spy.count(), 1);

    window.setAutoClose(true);
    ASSERT_TRUE(window.autoClose());
    ASSERT_EQ(spy.count(), 2);
}

TEST(QuickWindowTest, Closable)
{
    QuickWindow window;
    QSignalSpy spy(&window, &QuickWindow::closableChanged);
    ASSERT_TRUE(window.closable());

    window.setClosable(false);
    ASSERT_FALSE(window.closable());
    ASSERT_EQ(spy.count(), 1);

    window.setClosable(false);
    ASSERT_FALSE(window.closable());
    ASSERT_EQ(spy.count(), 1);

    window.setClosable(true);
    ASSERT_TRUE(window.closable());
    ASSERT_EQ(spy.count(), 2);
}

TEST(QuickWindowTest, KeyPressEvent)
{
    QuickWindow window;
    window.setAutoClose(true);
    window.setClosable(true);
    ASSERT_FALSE(window.isVisible());
    window.show();
    ASSERT_TRUE(window.isVisible());

    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, " ");
    QCoreApplication::sendEvent(&window, &event1);
    ASSERT_TRUE(window.isVisible());

    QKeyEvent event2(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier, "");
    QCoreApplication::sendEvent(&window, &event2);
    ASSERT_FALSE(window.isVisible());

    window.show();
    window.setAutoClose(false);
    QCoreApplication::sendEvent(&window, &event2);
    ASSERT_TRUE(window.isVisible());

    window.setClosable(false);
    QCoreApplication::sendEvent(&window, &event2);
    ASSERT_TRUE(window.isVisible());

    window.setAutoClose(true);
    QCoreApplication::sendEvent(&window, &event2);
    ASSERT_TRUE(window.isVisible());
}

TEST(QuickWindowTest, CloseEvent)
{
    QuickWindow window;
    window.setClosable(true);
    ASSERT_FALSE(window.isVisible());
    window.show();
    ASSERT_TRUE(window.isVisible());

    QCloseEvent event;
    QCoreApplication::sendEvent(&window, &event);
    ASSERT_FALSE(window.isVisible());

    window.setClosable(false);
    window.show();
    QCoreApplication::sendEvent(&window, &event);
    ASSERT_TRUE(window.isVisible());
}
