#include <gtest/gtest.h>
#include <QQmlEngine>
#include <QPushButton>
#include <QQuickItem>
#include <QSignalSpy>

#include "internal/uiengine.h"

using namespace scratchcpp::ui;

TEST(UiEngineTest, Instance)
{
    ASSERT_TRUE(UiEngine::instance());
}

TEST(UiEngineTest, QmlEngine)
{
    UiEngine engine;
    ASSERT_EQ(engine.qmlEngine(), nullptr);

    QQmlEngine qmlEngine;
    engine.setQmlEngine(&qmlEngine);
    ASSERT_EQ(engine.qmlEngine(), &qmlEngine);
}

TEST(UiEngineTest, StandardButtonText)
{
    static const std::vector<QDialogButtonBox::StandardButton> buttons = {
        QDialogButtonBox::Ok,       QDialogButtonBox::Open,    QDialogButtonBox::Save,
        QDialogButtonBox::Cancel,   QDialogButtonBox::Close,   QDialogButtonBox::Discard,
        QDialogButtonBox::Apply,    QDialogButtonBox::Reset,   QDialogButtonBox::RestoreDefaults,
        QDialogButtonBox::Help,     QDialogButtonBox::SaveAll, QDialogButtonBox::Yes,
        QDialogButtonBox::YesToAll, QDialogButtonBox::No,      QDialogButtonBox::NoToAll,
        QDialogButtonBox::Abort,    QDialogButtonBox::Retry,   QDialogButtonBox::Ignore
    };

    UiEngine engine;
    QDialogButtonBox dialogButtonBox;

    for (QDialogButtonBox::StandardButton button : buttons) {
        dialogButtonBox.addButton(button);
        ASSERT_EQ(engine.standardButtonText(button), dialogButtonBox.button(button)->text());
        ASSERT_FALSE(engine.standardButtonText(button).isEmpty());
    }
}

TEST(UiEngineTest, ActiveFocusItem)
{
    UiEngine engine;
    QSignalSpy spy(&engine, &UiEngine::activeFocusItemChanged);
    ASSERT_EQ(engine.activeFocusItem(), nullptr);

    QQuickItem item;
    engine.setActiveFocusItem(&item);
    ASSERT_EQ(engine.activeFocusItem(), &item);
    ASSERT_EQ(spy.count(), 1);
}
