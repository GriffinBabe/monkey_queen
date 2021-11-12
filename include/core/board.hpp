#pragma once

#include <cstdint>
#include <math.h>

namespace core {

// board width and height
constexpr std::uint8_t WIDTH = 8;
constexpr std::uint8_t HEIGHT = 8;

// bit boards are the representation of one type of piece one a chessboard
// the A8 square is the MSB while the H1 is the LSB
typedef std::uint64_t bitboard_t;

// generic bitboards

// the empty set
constexpr bitboard_t EMPTY = 0x0000000000000000;

// universe set (can also be marked as -1 as it is unsigned)
constexpr bitboard_t UNIVERSE = 0xFFFFFFFFFFFFFFFF;

// equals 1, can be combined with left shift to create a single cell mask
constexpr bitboard_t UNIT = 0x0000000000000001;

// const variable for setwise bitboards
constexpr std::uint8_t WHITE = 0;
constexpr std::uint8_t BLACK = 1;

// position of the EN PASSANT bitboard in the bitboards array
constexpr std::uint8_t EN_PASSANT = 12;

// position of the auxiliary data
constexpr std::uint8_t OTHER_DATA = 13;

// mask of the halfmove clock info in the auxiliary array
constexpr bitboard_t HALFMOVE_CLOCK_MASK = 0x000000000000FFFF;

// mask of the fullmove clock info in the auxiliary array
constexpr bitboard_t FULLMOVE_CLOCK_MASK = 0x00000000FFFF0000;

// mask of the castle info in the auxiliary array
constexpr bitboard_t PLAYER_TO_MOVE_MASK = 0x0000000100000000;

constexpr bitboard_t WHITE_K_CASTLE_MASK = 0x0000000200000000;

constexpr bitboard_t WHITE_Q_CASTLE_MASK = 0x0000000400000000;

constexpr bitboard_t BLACK_K_CASTLE_MASK = 0x0000000800000000;

constexpr bitboard_t BLACK_Q_CASTLE_MASK = 0x0000001000000000;

enum Piece { NONE = -1, PAWN = 0, KNIGHT = 1, BISHOP = 2, ROOK = 3, QUEEN = 4, KING = 5 };

class Board {
public:
    Board();

    ~Board();

    void clear_board();

    [[nodiscard]] constexpr bitboard_t get_piece_board(core::Piece piece,
                                                       bool color) const;

    [[nodiscard]] constexpr bitboard_t get_en_passant_board() const;

    [[nodiscard]] constexpr bitboard_t get_auxiliary_board() const;

    constexpr bitboard_t& get_piece_board(core::Piece piece, bool color);

    /**
     * Adds, moves or removes a piece by XORring the given bitboard with
     * the appropriate bitboard.
     * @param bb, given bitboard
     * @param piece, piece number
     * @param color, the piece color (0=white, 1=BLACK)
     */
    constexpr void set_piece(bitboard_t bb, Piece piece, std::uint8_t color);

    /**
     * Checks if white can castle on king's side.
     */
    [[nodiscard]] constexpr bool can_castle_white_king() const;

    /**
     * Checks if white can castle on queen's side.
     */
    [[nodiscard]] constexpr bool can_castle_white_queen() const;

    /**
     * Checks if black can castle on king's side.
     */
    [[nodiscard]] constexpr bool can_castle_black_king() const;

    /**
     * Checks if black can castle on queen's side.
     */
    [[nodiscard]] constexpr bool can_castle_black_queen() const;

    /**
     * Returns the bitboard with the available en passant cell
     */
    [[nodiscard]] constexpr bitboard_t get_en_passant() const;

    /**
     * Returns the half turn clock number
     */
    [[nodiscard]] constexpr std::uint16_t get_half_turn_clock() const;

    /**
     * Returns the full turn clock number
     */
    [[nodiscard]] constexpr std::uint16_t get_full_turn_clock() const;

    /**
     * Returns which player to move
     */
     [[nodiscard]] constexpr std::uint8_t get_player_to_move() const;

    /**
     * Makes the white king's side castle possible
     */
    constexpr void set_castle_white_king(bool value = true);

    /**
     * Makes the white king's side castle possible
     */
    constexpr void set_castle_white_queen(bool value = true);

    /**
     * Makes the white king's side castle possible
     */
    constexpr void set_castle_black_king(bool value = true);

    /**
     * Makes the white king's side castle possible
     */
    constexpr void set_castle_black_queen(bool value = true);

    /**
     * Sets the board en passant bitboard
     *
     * @param board, the en passant bitboard containing the position
     */
    constexpr void set_en_passant(bitboard_t board);

    /**
     * Sets the value of the half turn clock.
     *
     * @param value, the value of the half turn clock, encoded on 16 bits.
     */
    constexpr void set_half_turn_clock(std::uint16_t value);

    /**
     * Sets the value of the full turn clock.
     *
     * @param value, the value of the full turn clock, encoded on 16 bits.
     */
     constexpr void set_full_turn_clock(std::uint16_t value);

     /**
      * Sets which player has to move now.
      *
      * @param value, either WHITE or BLACK
      */
     constexpr void set_player_to_move(std::uint8_t value);

private:
    /**
     * Board data, each bitboard_t contains the presence of a type of piece on
     * the board with the exception of the two last bitboards.
     *
     * The 14th bitboard contains multiple information.
     *  - 16bit Halfmove clock (number of half move before the last capture
     *  or pawn advance)
     *  - 16bit Fullmove clock (number of full moves white & black)
     *  - 1bit player to move (white = 0, black = 1)
     *  - 4bit castles possibilities (in order: white king, white queen, black
     * king, black queen)
     *  - the rest of the bites is reserved space for later additional info
     */
    bitboard_t _board[14];
};


constexpr core::bitboard_t core::Board::get_piece_board(core::Piece piece,
                                                        bool color) const
{
    return _board[piece + 6 * color];
}

constexpr core::bitboard_t& core::Board::get_piece_board(core::Piece piece,
                                                         bool color)
{
    return _board[piece + 6 * color];
}

[[nodiscard]] constexpr bitboard_t core::Board::get_en_passant_board() const
{
    return _board[EN_PASSANT];
}

[[nodiscard]] constexpr bitboard_t core::Board::get_auxiliary_board() const
{
    return _board[OTHER_DATA];
}

constexpr void core::Board::set_piece(core::bitboard_t bb,
                                      core::Piece piece,
                                      std::uint8_t color)
{
    bitboard_t& piece_board = get_piece_board(piece, color);
    piece_board ^= bb; //
}

constexpr bool core::Board::can_castle_white_king() const
{
    return _board[OTHER_DATA] & WHITE_K_CASTLE_MASK;
}

constexpr bool core::Board::can_castle_white_queen() const
{
    return _board[OTHER_DATA] & WHITE_Q_CASTLE_MASK;
}

constexpr bool core::Board::can_castle_black_king() const
{
    return _board[OTHER_DATA] & BLACK_K_CASTLE_MASK;
}

constexpr bool core::Board::can_castle_black_queen() const
{
    return _board[OTHER_DATA] & BLACK_Q_CASTLE_MASK;
}

constexpr void core::Board::set_castle_white_king(bool value)
{
    bitboard_t castle = ((bitboard_t) (value > 0)) << 33u;
    _board[OTHER_DATA] = (_board[OTHER_DATA] & ~WHITE_K_CASTLE_MASK) + castle;
}

constexpr void core::Board::set_castle_white_queen(bool value)
{
    bitboard_t castle = ((bitboard_t) (value > 0)) << 34u;
    _board[OTHER_DATA] = (_board[OTHER_DATA] & ~WHITE_Q_CASTLE_MASK) + castle;
}

constexpr void core::Board::set_castle_black_king(bool value)
{
    bitboard_t castle = ((bitboard_t) (value > 0)) << 35u;
    _board[OTHER_DATA] = (_board[OTHER_DATA] & ~BLACK_K_CASTLE_MASK) + castle;
}

constexpr void core::Board::set_castle_black_queen(bool value)
{
    bitboard_t castle = ((bitboard_t) (value > 0)) << 36u;
    _board[OTHER_DATA] = (_board[OTHER_DATA] & ~BLACK_Q_CASTLE_MASK) + castle;
}

constexpr void core::Board::set_en_passant(core::bitboard_t board)
{
    _board[EN_PASSANT] = board;
}

constexpr void core::Board::set_half_turn_clock(std::uint16_t value)
{
    bitboard_t half_turn = value;
    _board[OTHER_DATA] =
        (~HALFMOVE_CLOCK_MASK & _board[OTHER_DATA]) + half_turn;
}

constexpr void core::Board::set_full_turn_clock(std::uint16_t value)
{
    // position of the rightmost set bit
    bitboard_t full_turn = value << 16u;
    _board[OTHER_DATA] =
        (~FULLMOVE_CLOCK_MASK & _board[OTHER_DATA]) + full_turn;
}

constexpr void core::Board::set_player_to_move(std::uint8_t value)
{
    // sets (value > 0) to truncate the value to only one bit
    bitboard_t to_move = (value > 0) << 17u;
    _board[OTHER_DATA] = (~PLAYER_TO_MOVE_MASK & _board[OTHER_DATA]) + to_move;
}

constexpr bitboard_t core::Board::get_en_passant() const
{
    return _board[EN_PASSANT];
}

constexpr std::uint16_t core::Board::get_half_turn_clock() const
{
    return (std::uint16_t) _board[OTHER_DATA] & HALFMOVE_CLOCK_MASK;
}

constexpr std::uint16_t core::Board::get_full_turn_clock() const
{
    return (std::uint16_t) ((_board[OTHER_DATA] & FULLMOVE_CLOCK_MASK) >> 16u);
}

constexpr std::uint8_t Board::get_player_to_move() const
{
    return (std::uint8_t) (_board[OTHER_DATA] & PLAYER_TO_MOVE_MASK) > 0;
}

} // namespace core
