set(MODULE global)
set(MODULE_URI Global)
set(MODULE_SRC
    globalmodule.cpp
    globalmodule.h
    iappinfo.h
    modularity/ioc.h
    modularity/modulesioc.h
    modularity/imoduleexportinterface.h
    modularity/imodulesetup.h
    internal/appinfo.cpp
    internal/appinfo.h
)

include(${PROJECT_SOURCE_DIR}/build/module.cmake)

include(FetchContent)
FetchContent_Declare(cmake_git_version_tracking
  GIT_REPOSITORY https://github.com/andrew-hardin/cmake-git-version-tracking.git
  GIT_TAG 904dbda1336ba4b9a1415a68d5f203f576b696bb
)
FetchContent_MakeAvailable(cmake_git_version_tracking)

target_link_libraries(${MODULE} PRIVATE cmake_git_version_tracking)
string(TIMESTAMP BUILD_YEAR "%Y")
target_compile_definitions(${MODULE} PRIVATE BUILD_YEAR=${BUILD_YEAR})

add_subdirectory(test)
