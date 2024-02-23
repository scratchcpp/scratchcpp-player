// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define MODULE_EXPORT_INTERFACE                                                                                                                                                                        \
public                                                                                                                                                                                                 \
    scratchcpp::modularity::IModuleExportInterface

namespace scratchcpp::modularity
{

class IModuleExportInterface
{
    public:
        virtual ~IModuleExportInterface() { }
};

} // namespace scratchcpp::modularity
