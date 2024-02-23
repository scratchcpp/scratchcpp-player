#pragma once

#include <modularity/imoduleexportinterface.h>
#include <modularity/ioc.h>

#include "fakedependency.h"

namespace scratchcpp
{

class FakeExport : MODULE_EXPORT_INTERFACE
{
        INJECT(FakeDependency, dep);
};

} // namespace scratchcpp
