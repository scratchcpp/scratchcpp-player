if (SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS)
    set(TARGET ${MODULE}_test)
    set(TEST_MAIN_SRC ${PROJECT_SOURCE_DIR}/test/main.cpp)

    include(GoogleTest)

    add_executable(
      ${TARGET}
      ${TEST_MAIN_SRC}
      ${MODULE_TEST_SRC}
    )

    target_link_libraries(
      ${TARGET}
      ${MODULE}
      GTest::gtest_main
      GTest::gmock_main
      Qt6::Gui
      Qt6::Qml
      Qt6::Test
    )

    target_include_directories(${TARGET} PRIVATE ${MODULE_SRC_DIR})
    target_include_directories(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_include_directories(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/src/global)
    gtest_discover_tests(${TARGET})
endif()
