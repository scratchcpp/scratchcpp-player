// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>

#include "ifilepaths.h"

namespace scratchcpp
{

class FilePaths : public IFilePaths
{
    public:
        static std::shared_ptr<FilePaths> instance();

        QString configLocation() const override;

    private:
        static std::shared_ptr<FilePaths> m_instance;
};

} // namespace scratchcpp
