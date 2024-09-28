#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFile>

#include "mocks/filepathsmock.h"

#include "internal/settings.h"

using namespace scratchcpp;

using ::testing::Return;

class SettingsTest : public testing::Test
{
    public:
        void SetUp() override
        {
            m_paths = std::make_shared<FilePathsMock>();
            modularity::ioc()->registerExport<IFilePaths>(m_paths);
            EXPECT_CALL(*m_paths, configLocation())
                .WillRepeatedly(Return(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/" + qApp->applicationName() + "/config_test.ini"));
            QFile::remove(m_paths->configLocation());
            m_settings = std::make_shared<Settings>();
        }

        void TearDown() override
        {
            modularity::ioc()->reset();
            m_settings->setpaths(nullptr);
        }

        std::shared_ptr<Settings> m_settings;
        std::shared_ptr<FilePathsMock> m_paths;
};

TEST_F(SettingsTest, SetGetContains)
{
    ASSERT_FALSE(m_settings->containsKey("test", "something"));
    ASSERT_TRUE(m_settings->getValue("test", "something").isNull());

    m_settings->setValue("test", "something", "hello world");
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_FALSE(m_settings->containsKey("test", "test"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello world");
    ASSERT_TRUE(m_settings->getValue("test", "test").isNull());

    m_settings->setValue("test", "test", 10);
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_TRUE(m_settings->containsKey("test", "test"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello world");
    ASSERT_EQ(m_settings->getValue("test", "test").toInt(), 10);

    ASSERT_FALSE(m_settings->containsKey("test2", "something"));
    ASSERT_FALSE(m_settings->containsKey("test2", "test"));
    ASSERT_TRUE(m_settings->getValue("test2", "something").isNull());
    ASSERT_TRUE(m_settings->getValue("test2", "test").isNull());

    m_settings->setValue("test2", "test", true);
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_TRUE(m_settings->containsKey("test", "test"));
    ASSERT_FALSE(m_settings->containsKey("test2", "something"));
    ASSERT_TRUE(m_settings->containsKey("test2", "test"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello world");
    ASSERT_TRUE(m_settings->getValue("test2", "test").toBool());
    ASSERT_TRUE(m_settings->getValue("test2", "something").isNull());

    // Test persistence
    m_settings.reset();
    m_settings = std::make_shared<Settings>();
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello world");
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_TRUE(m_settings->containsKey("test", "test"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello world");
    ASSERT_EQ(m_settings->getValue("test", "test").toInt(), 10);
    ASSERT_TRUE(m_settings->getValue("test2", "test").toBool());
    ASSERT_TRUE(m_settings->getValue("test2", "something").isNull());
}

TEST_F(SettingsTest, DefaultValue)
{
    m_settings->addKey("test", "something", 5);
    ASSERT_FALSE(m_settings->containsKey("test", "something"));
    ASSERT_EQ(m_settings->getValue("test", "something").toInt(), 5);

    m_settings->setValue("test", "something", 10);
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_EQ(m_settings->getValue("test", "something").toInt(), 10);
}

TEST_F(SettingsTest, Freeze)
{
    ASSERT_FALSE(m_settings->isFrozen());

    // Discard
    m_settings->setValue("test", "something", "hello");
    m_settings->freeze();
    ASSERT_TRUE(m_settings->isFrozen());
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello");

    m_settings->setValue("test", "test", 15);
    ASSERT_TRUE(m_settings->containsKey("test", "test"));
    ASSERT_EQ(m_settings->getValue("test", "test").toInt(), 15);

    m_settings->discardChanges();
    ASSERT_FALSE(m_settings->isFrozen());
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello");
    ASSERT_FALSE(m_settings->containsKey("test", "test"));
    ASSERT_TRUE(m_settings->getValue("test", "test").isNull());

    // Save
    m_settings->freeze();
    ASSERT_TRUE(m_settings->isFrozen());
    m_settings->setValue("test", "test", 15);

    m_settings->saveChanges();
    ASSERT_FALSE(m_settings->isFrozen());
    ASSERT_TRUE(m_settings->containsKey("test", "something"));
    ASSERT_EQ(m_settings->getValue("test", "something").toString(), "hello");
    ASSERT_TRUE(m_settings->containsKey("test", "test"));
    ASSERT_EQ(m_settings->getValue("test", "test").toInt(), 15);
}
