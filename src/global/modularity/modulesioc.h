// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <unordered_set>
#include <vector>
#include <memory>
#include <cassert>
#include "imoduleexportinterface.h"

namespace scratchcpp::modularity
{

class ModulesIoC
{
    public:
        static ModulesIoC *instance()
        {
            static ModulesIoC instance;
            return &instance;
        }

        template<class I>
        void registerExport(std::shared_ptr<I> instance)
        {
            // Remove old exports of this class
            std::vector<std::shared_ptr<IModuleExportInterface>> toRemove;

            for (auto ex : m_exports) {
                std::shared_ptr<I> exCast = std::dynamic_pointer_cast<I>(ex);

                if (exCast)
                    toRemove.push_back(exCast);
            }

            for (auto ex : toRemove)
                m_exports.erase(ex);

            // Register the export
            auto iface = std::dynamic_pointer_cast<IModuleExportInterface>(instance);
            assert(m_exports.find(iface) == m_exports.end());

            if (!iface) {
                assert(false);
                return;
            }

            m_exports.insert(iface);
        }

        template<class I>
        std::shared_ptr<I> resolve() const
        {
            for (auto ex : m_exports) {
                std::shared_ptr<I> exCast = std::dynamic_pointer_cast<I>(ex);
                if (exCast)
                    return exCast;
            }

            return nullptr;
        }

    private:
        std::unordered_set<std::shared_ptr<IModuleExportInterface>> m_exports;
};

} // namespace scratchcpp::modularity
