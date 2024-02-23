set(MODULE global)
set(MODULE_URI Global)
set(MODULE_SRC
    globalmodule.cpp
    globalmodule.h
    modularity/ioc.h
    modularity/modulesioc.h
    modularity/imoduleexportinterface.h
    modularity/imodulesetup.h
)

include(${PROJECT_SOURCE_DIR}/build/module.cmake)

add_subdirectory(test)
