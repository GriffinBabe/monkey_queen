add_executable(fen_test
        fen_test.cpp)

target_link_libraries(fen_test PUBLIC core GTest::Main)

gtest_discover_tests(fen_test)

