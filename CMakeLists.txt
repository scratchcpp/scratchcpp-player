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

add_subdirectory(src)
add_subdirectory(res)

set_target_properties(appscratchcpp-player PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appscratchcpp-player
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appscratchcpp-player
    PRIVATE Qt6::Quick Qt6::QuickControls2)

set(SCRATCHCPPRENDER_BUILD_UNIT_TESTS OFF)
add_subdirectory(scratchcpp-render)
target_link_libraries(appscratchcpp-player PRIVATE scratchcpp-render scratchcpp-renderplugin)
