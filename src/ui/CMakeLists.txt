set(MODULE ui)
set(MODULE_URI Ui)
set(MODULE_SRC
    uimodule.cpp
    uimodule.h
    iuiengine.h
    ithemeengine.h
    internal/uiengine.cpp
    internal/uiengine.h
    internal/themeengine.cpp
    internal/themeengine.h
)

include(${PROJECT_SOURCE_DIR}/build/module.cmake)

add_subdirectory(test)
