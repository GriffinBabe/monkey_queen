#include <core/board.hpp>
#include <core/fen.hpp>
#include <core/util.hpp>
#include <gtest/gtest.h>
#include <math.h>

constexpr auto fen_starting_position =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

constexpr auto fen_too_many_args =
    "rnbq kbnr/ppppppp p/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 w 2";

constexpr auto fen_too_few_args =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";

constexpr auto fen_invalid_piece =
    "rnbqkbnr/pppppZpp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";

constexpr auto fen_incomplete_board =
    "rnbkbnr/pppppp/8/5/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

constexpr auto fen_wrong_player_to_move =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR g KQkq - 0 1";

constexpr auto fen_wrong_castles =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w ZQkz - 0 1";

constexpr auto fen_wrong_en_passant_1 =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq z8 0 1";

constexpr auto fen_wrong_en_passant_2 =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq 8a 0 1";

class FenTest : public ::testing::Test {
    friend class core::Board;
};

TEST_F(FenTest, test_bitwise_operators_1)
{
    // find the rightmost set bit
    core::bitboard_t complement = -core::FULLMOVE_CLOCK_MASK;
    core::bitboard_t bitwise_and = complement & core::FULLMOVE_CLOCK_MASK;

    ASSERT_EQ(log2(bitwise_and), 16);

    // check if the bitshift is well defined
    // util::print_bitboard(core::HALFMOVE_CLOCK_MASK << 16u);
    ASSERT_EQ(core::HALFMOVE_CLOCK_MASK << 16u, core::FULLMOVE_CLOCK_MASK);
}

TEST_F(FenTest, from_fen_starting_position)
{
    const core::Board board = core::from_fen(fen_starting_position);

    // check that al the bitboard from all pieces are well initialized
    core::bitboard_t black_pawn =
        board.get_piece_board(core::PAWN, core::BLACK);
    ASSERT_EQ(black_pawn, 0x000000000000FF00);

    core::bitboard_t black_rook =
        board.get_piece_board(core::ROOK, core::BLACK);
    ASSERT_EQ(black_rook, 0x0000000000000081);

    core::bitboard_t black_knight =
        board.get_piece_board(core::KNIGHT, core::BLACK);
    ASSERT_EQ(black_knight, 0x0000000000000042);

    core::bitboard_t black_bishop =
        board.get_piece_board(core::BISHOP, core::BLACK);
    ASSERT_EQ(black_bishop, 0x0000000000000024);

    core::bitboard_t black_queen =
        board.get_piece_board(core::QUEEN, core::BLACK);
    ASSERT_EQ(black_queen, 0x0000000000000008);

    core::bitboard_t black_king =
        board.get_piece_board(core::KING, core::BLACK);
    ASSERT_EQ(black_king, 0x0000000000000010);

    // same for white
    core::bitboard_t white_pawn =
        board.get_piece_board(core::PAWN, core::WHITE);
    ASSERT_EQ(white_pawn, 0x00FF000000000000);

    core::bitboard_t white_rook =
        board.get_piece_board(core::ROOK, core::WHITE);
    ASSERT_EQ(white_rook, 0x8100000000000000);

    core::bitboard_t white_knight =
        board.get_piece_board(core::KNIGHT, core::WHITE);
    ASSERT_EQ(white_knight, 0x4200000000000000);

    core::bitboard_t white_bishop =
        board.get_piece_board(core::BISHOP, core::WHITE);
    ASSERT_EQ(white_bishop, 0x2400000000000000);

    core::bitboard_t white_queen =
        board.get_piece_board(core::QUEEN, core::WHITE);
    ASSERT_EQ(white_queen, 0x0800000000000000);

    core::bitboard_t white_king =
        board.get_piece_board(core::KING, core::WHITE);
    ASSERT_EQ(white_king, 0x1000000000000000);

    // check for en passant cells
    ASSERT_EQ(board.get_en_passant(), 0x0000000000000000);

    // checks for half turn clock, full turn clock and castles
    ASSERT_EQ(board.get_half_turn_clock(), 0);

    ASSERT_EQ(board.get_full_turn_clock(), 1);

    ASSERT_TRUE(board.can_castle_black_king());
    ASSERT_TRUE(board.can_castle_black_queen());
    ASSERT_TRUE(board.can_castle_white_king());
    ASSERT_TRUE(board.can_castle_white_queen());
}

TEST_F(FenTest, fen_wrong_expressions)
{
    std::vector<const char*> expressions = {fen_too_many_args,
                                            fen_too_few_args,
                                            fen_wrong_castles,
                                            fen_wrong_en_passant_1,
                                            fen_wrong_en_passant_2,
                                            fen_wrong_player_to_move,
                                            fen_incomplete_board,
                                            fen_invalid_piece};
    for (const auto* expression : expressions) {
        try {
            auto board = core::from_fen(expression);
            FAIL();
        }
        catch (std::runtime_error const& err) {
            std::cout << err.what() << std::endl;
        }
    }
}
