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

class ThemeEngineTest : public testing::Test
{
    public:
        void SetUp() override
        {
            m_settings = std::make_shared<SettingsMock>();
            m_themeEngine.setsettings(m_settings);

            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::themeChanged));
            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::bgColorChanged));
            m_themeSpies.push_back(std::make_unique<QSignalSpy>(&m_themeEngine, &ThemeEngine::borderColorChanged));
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
