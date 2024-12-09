cmake_minimum_required(VERSION 3.16)

project(scratchcpp-player VERSION 0.5.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS "Build unit tests" ON)

find_package(Qt6 6.6 COMPONENTS Quick QuickControls2 Widgets OpenGLWidgets REQUIRED)
set(QT_LIBS Qt6::Quick Qt6::QuickControls2 Qt6::Widgets Qt6::OpenGLWidgets)

if (LINUX)
    find_package(Qt6 6.6 COMPONENTS DBus REQUIRED)
    set(QT_LIBS ${QT_LIBS} Qt6::DBus)
endif()

if (SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS)
    set(GTEST_DIR thirdparty/googletest)
    add_subdirectory(${PROJECT_SOURCE_DIR}/${GTEST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${GTEST_DIR})
    enable_testing()
    find_package(Qt6 6.6 COMPONENTS Test REQUIRED)
endif()

set(SCRATCHCPPRENDER_BUILD_UNIT_TESTS OFF)
add_subdirectory(scratchcpp-render)

add_subdirectory(src)
add_subdirectory(res)
