add_executable(fen_test
        fen_test.cpp)

add_executable(board_test
        board_test.cpp)

target_link_libraries(fen_test PUBLIC core GTest::Main)
target_link_libraries(board_test PUBLIC core GTest::Main)

gtest_discover_tests(fen_test)
gtest_discover_tests(board_test)

