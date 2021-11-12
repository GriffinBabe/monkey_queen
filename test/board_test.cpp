#include <gtest/gtest.h>
#include <core/board.hpp>
#include <core/util.hpp>
#include <core/fen.hpp>

constexpr auto fen_starting_position =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class BoardTest : public ::testing::Test {
    friend class core::Board;
};

TEST_F(BoardTest, test_bitwise_operators_1)
{
    // find the rightmost set bit
    core::bitboard_t complement = -core::FULLMOVE_CLOCK_MASK;
    core::bitboard_t bitwise_and = complement & core::FULLMOVE_CLOCK_MASK;

    ASSERT_EQ(log2(bitwise_and), 16);

    // check if the bitshift is well defined
    // util::print_bitboard(core::HALFMOVE_CLOCK_MASK << 16u);
    ASSERT_EQ(core::HALFMOVE_CLOCK_MASK << 16u, core::FULLMOVE_CLOCK_MASK);
}

TEST_F(BoardTest, test_castle_toggles)
{
    core::Board board = core::from_fen(fen_starting_position);

    // removes all the castle possibilities
    board.set_castle_black_queen(false);
    board.set_castle_black_king(false);
    board.set_castle_white_queen(false);
    board.set_castle_white_king(false);

    // check if the castles are unavailable
    ASSERT_FALSE(board.can_castle_white_queen());
    ASSERT_FALSE(board.can_castle_white_king());
    ASSERT_FALSE(board.can_castle_black_queen());
    ASSERT_FALSE(board.can_castle_black_king());
}