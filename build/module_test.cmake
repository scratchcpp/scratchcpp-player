if (SCRATCHCPP_PLAYER_BUILD_UNIT_TESTS)
    set(TARGET ${MODULE}_test)
    set(TEST_MAIN_SRC ${PROJECT_SOURCE_DIR}/test/main.cpp)
    set(GTEST_DIR thirdparty/googletest)
    add_subdirectory(${PROJECT_SOURCE_DIR}/${GTEST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${GTEST_DIR})

    include(GoogleTest)

    add_executable(
      ${TARGET}
      ${TEST_MAIN_SRC}
      ${MODULE_TEST_SRC}
    )

    target_link_libraries(
      ${TARGET}
      GTest::gtest_main
      GTest::gmock_main
      Qt6::Gui
      Qt6::Test
    )

    target_include_directories(${TARGET} PRIVATE ${MODULE_SRC_DIR})
endif()
