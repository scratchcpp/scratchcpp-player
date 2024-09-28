#pragma once

#include <ifilepaths.h>
#include <gmock/gmock.h>

namespace scratchcpp
{

class FilePathsMock : public IFilePaths
{
    public:
        MOCK_METHOD(QString, configLocation, (), (const, override));
};

} // namespace scratchcpp
