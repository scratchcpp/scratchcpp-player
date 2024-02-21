set(MODULE_TEST_SRC
    modularity.cpp
    fakeexport.h
    fakedependency.h
    mocks/moduleexportinterfacemock.h
    mocks/modulesetupmock.h
)

include(${PROJECT_SOURCE_DIR}/build/module_test.cmake)
