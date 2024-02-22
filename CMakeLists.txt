cmake_minimum_required(VERSION 3.16)

project(scratchcpp-player VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS "Build unit tests" ON)

find_package(Qt6 6.6 COMPONENTS Quick QuickControls2 REQUIRED)

if (SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS)
    enable_testing()
    find_package(Qt6 6.6 COMPONENTS Test REQUIRED)
endif()

set(SCRATCHCPPRENDER_BUILD_UNIT_TESTS OFF)
add_subdirectory(scratchcpp-render)

add_subdirectory(src)
add_subdirectory(res)
