set(MODULE keyboard)
set(MODULE_URI Keyboard)
set(MODULE_SRC
    keyboardmodule.cpp
    keyboardmodule.h
    ikeyboardinfo.h
    internal/keyboardinfo.cpp
    internal/keyboardinfo.h
)

include(${PROJECT_SOURCE_DIR}/build/module.cmake)
