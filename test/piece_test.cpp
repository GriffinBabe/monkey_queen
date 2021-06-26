#include <core/piece.hpp>
#include <gtest/gtest.h>

class PieceTest : public ::testing::Test {
};

TEST_F(PieceTest, test_piece_enumeration)
{
    core::uchar white_monkey = core::Piece::WHITE | core::Piece::MONKEY;
    core::uchar black_monkey = core::Piece::BLACK | core::Piece::MONKEY;
    core::uchar white_queen = core::Piece::WHITE | core::Piece::QUEEN;
    core::uchar black_queen = core::Piece::BLACK | core::Piece::QUEEN;
    core::uchar none = core::Piece::NONE;

    ASSERT_TRUE(
        core::piece_is(white_monkey, core::Piece::MONKEY, core::Piece::WHITE));
    ASSERT_TRUE(
        core::piece_is(black_monkey, core::Piece::MONKEY, core::Piece::BLACK));
    ASSERT_TRUE(
        core::piece_is(white_queen, core::Piece::QUEEN, core::Piece::WHITE));
    ASSERT_TRUE(
        core::piece_is(black_queen, core::Piece::QUEEN, core::Piece::BLACK));

    ASSERT_FALSE(
        core::piece_is(white_monkey, core::Piece::MONKEY, core::Piece::BLACK));
    ASSERT_FALSE(
        core::piece_is(black_monkey, core::Piece::QUEEN, core::Piece::BLACK));
    ASSERT_FALSE(
        core::piece_is(white_queen, core::Piece::MONKEY, core::Piece::BLACK));
}