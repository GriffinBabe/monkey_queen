add_executable(piece_test
        piece_test.cpp)

target_link_libraries(piece_test PUBLIC core GTest::Main)

add_executable(fen_test
                fen_test.cpp)

target_link_libraries(fen_test PUBLIC core GTest::Main)

gtest_discover_tests(piece_test)
