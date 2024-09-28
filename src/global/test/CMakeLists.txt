set(MODULE_TEST_SRC
    modularity.cpp
    setup.cpp
    appinfo.cpp
    settings.cpp
    fakeexport.h
    fakedependency.h
    mocks/moduleexportinterfacemock.h
    mocks/modulesetupmock.h
)

include(${PROJECT_SOURCE_DIR}/build/module_test.cmake)

if (SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS)
    set(TARGET ${MODULE}_test)
    target_link_libraries(${TARGET} cmake_git_version_tracking)
    string(TIMESTAMP BUILD_YEAR "%Y")
    target_compile_definitions(${TARGET} PRIVATE BUILD_YEAR=${BUILD_YEAR})
endif()
