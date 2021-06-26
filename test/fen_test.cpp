#include <core/board.hpp>
#include <core/fen.hpp>
#include <core/piece.hpp>
#include <gtest/gtest.h>

constexpr auto fen_notation_start = "4q3/8/8/8/8/8/8/3Q4 w - 0 - 8 - 8";

constexpr auto fen_notation_two_moves = "4mq2/8/8/8/8/8/8/2QM4 w - 1 - 7 - 7";

constexpr auto fen_notation_one_move = "4q3/8/8/8/8/8/3Q4/3M4 b - 0 - 7 - 8";

class FenTest : public ::testing::Test {
};

TEST_F(FenTest, to_fen_starting_position)
{
    constexpr int cols = 8, rows = 8, stack = 8;

    core::uchar initial_position[cols * rows] = {0};
    initial_position[4] = core::Piece::QUEEN | core::Piece::BLACK;
    initial_position[3 + (rows - 1) * cols] =
        core::Piece::QUEEN | core::Piece::WHITE;

    core::Board board(cols, rows, stack, 0, core::Team::WHITE_T);
    board.set_board(&(initial_position[0]), cols * rows);

    const std::string fen = core::to_fen(board);

    ASSERT_TRUE(strcmp(fen_notation_start, fen.c_str()) == 0);
}

TEST_F(FenTest, from_fen_starting_position)
{
    core::Board board = core::from_fen(fen_notation_start);

    ASSERT_TRUE(board.cols() == 8);
    ASSERT_TRUE(board.rows() == 8);
    ASSERT_TRUE(board.stack(core::WHITE_T) == 8);
    ASSERT_TRUE(board.stack(core::BLACK_T) == 8);
    ASSERT_TRUE(board.turn() == 0);
}

TEST_F(FenTest, from_fen_one_move)
{
    core::Board board = core::from_fen(fen_notation_one_move);

    ASSERT_TRUE(board.cols() == 8);
    ASSERT_TRUE(board.rows() == 8);
    ASSERT_TRUE(board.stack(core::WHITE_T) == 7);
    ASSERT_TRUE(board.stack(core::BLACK_T) == 8);
    ASSERT_TRUE(board.turn() == 0);

    const core::uchar* array = board.board();
    core::uchar black_queen = array[4];
    core::uchar white_queen = array[6 * 8 + 3];
    core::uchar white_monkey = array[7 * 8 + 3];

    ASSERT_TRUE(
        core::piece_is(black_queen, core::Piece::QUEEN, core::Piece::BLACK));
    ASSERT_TRUE(
        core::piece_is(white_monkey, core::Piece::MONKEY, core::Piece::WHITE));
    ASSERT_TRUE(
        core::piece_is(white_queen, core::Piece::QUEEN, core::Piece::WHITE));
}

TEST_F(FenTest, from_fen_two_moves)
{
    // fen position after two moves
    core::Board board = core::from_fen(fen_notation_two_moves);

    ASSERT_TRUE(board.cols() == 8);
    ASSERT_TRUE(board.rows() == 8);
    ASSERT_TRUE(board.stack(core::WHITE_T) == 7);
    ASSERT_TRUE(board.stack(core::BLACK_T) == 7);
    ASSERT_TRUE(board.turn() == 1);
    ASSERT_TRUE(board.playing() == core::WHITE_T);
}
