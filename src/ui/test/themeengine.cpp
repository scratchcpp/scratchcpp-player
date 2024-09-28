#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QSignalSpy>

#include "mocks/settingsmock.h"

#include "internal/themeengine.h"

using namespace scratchcpp;

using ::testing::Return;
using ::testing::_;

static const QString MODULE = "ui";
static const QString THEME_KEY = "theme";
static const QString ACCENT_COLOR_KEY = "accentColor";

class ThemeEngineTest : public testing::Test
{
    public:
        void SetUp() override
        {
            m_settings = std::make_shared<SettingsMock>();
            m_themeEngine.setsettings(m_settings);

            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::themeChanged));
            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::bgColorChanged));
            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::foregroundColorChanged));
            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::borderColorChanged));
            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::accentColorChanged));
        }

        void TearDown() override { m_themeEngine.setsettings(nullptr); }

        void checkThemeSpies(int count)
        {
            for (const auto &spy : m_themeSpies)
                ASSERT_EQ(spy->count(), count);
        }

        ThemeEngine m_themeEngine;
        std::shared_ptr<SettingsMock> m_settings;
        std::vector<std::unique_ptr<QSignalSpy>> m_themeSpies;
};

TEST_F(ThemeEngineTest, Instance)
{
    ASSERT_TRUE(ThemeEngine::instance());
}

TEST_F(ThemeEngineTest, Theme)
{
    EXPECT_CALL(*m_settings, getValue(MODULE, THEME_KEY)).WillOnce(Return(0));
    ASSERT_EQ(m_themeEngine.theme(), ThemeEngine::Theme::DarkTheme);

    EXPECT_CALL(*m_settings, getValue(MODULE, THEME_KEY)).WillOnce(Return(1));
    ASSERT_EQ(m_themeEngine.theme(), ThemeEngine::Theme::LightTheme);
    checkThemeSpies(0);

    EXPECT_CALL(*m_settings, setValue(MODULE, THEME_KEY, QVariant(0)));
    m_themeEngine.setTheme(ThemeEngine::Theme::DarkTheme);
    checkThemeSpies(1);

    EXPECT_CALL(*m_settings, setValue(MODULE, THEME_KEY, QVariant(1)));
    m_themeEngine.setTheme(ThemeEngine::Theme::LightTheme);
    checkThemeSpies(2);

    EXPECT_CALL(*m_settings, setValue(MODULE, THEME_KEY, _));
    m_themeEngine.resetTheme();
    checkThemeSpies(3);

    m_themeEngine.reloadTheme();
    checkThemeSpies(4);
}

TEST_F(ThemeEngineTest, AccentColor)
{
    QSignalSpy spy(&m_themeEngine, &ThemeEngine::accentColorChanged);

    EXPECT_CALL(*m_settings, getValue(MODULE, ACCENT_COLOR_KEY)).WillOnce(Return(QColor(255, 0, 0)));
    ASSERT_EQ(m_themeEngine.accentColor(), QColor(255, 0, 0));
    ASSERT_EQ(spy.count(), 0);

    EXPECT_CALL(*m_settings, getValue(MODULE, ACCENT_COLOR_KEY)).WillOnce(Return(QColor(0, 255, 128)));
    ASSERT_EQ(m_themeEngine.accentColor(), QColor(0, 255, 128));
    ASSERT_EQ(spy.count(), 0);

    EXPECT_CALL(*m_settings, setValue(MODULE, ACCENT_COLOR_KEY, QVariant(QColor(255, 255, 255))));
    m_themeEngine.setAccentColor(QColor(255, 255, 255));
    ASSERT_EQ(spy.count(), 1);

    EXPECT_CALL(*m_settings, setValue(MODULE, ACCENT_COLOR_KEY, QVariant(QColor(0, 0, 0))));
    m_themeEngine.setAccentColor(QColor(0, 0, 0));
    ASSERT_EQ(spy.count(), 2);
}
