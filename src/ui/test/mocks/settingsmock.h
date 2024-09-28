#pragma once

#include <isettings.h>
#include <gmock/gmock.h>

namespace scratchcpp
{

class SettingsMock : public ISettings
{
    public:
        MOCK_METHOD(void, addKey, (const QString &, const QString &, const QVariant &), (override));
        MOCK_METHOD(void, setValue, (const QString &, const QString &, const QVariant &), (override));
        MOCK_METHOD(QVariant, getValue, (const QString &, const QString &), (const, override));
        MOCK_METHOD(bool, containsKey, (const QString &, const QString &), (const, override));

        MOCK_METHOD(void, freeze, (), (override));
        MOCK_METHOD(void, saveChanges, (), (override));
        MOCK_METHOD(void, discardChanges, (), (override));
        MOCK_METHOD(bool, isFrozen, (), (const, override));
};

} // namespace scratchcpp
