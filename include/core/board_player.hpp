#pragma once
#include "core/board.hpp"
#include "core/fen.hpp"
#include "core/util.hpp"

namespace core {

struct Move {
    /**
     * Starting position
     */
    core::bitboard_t start = 0;

    /**
     * Exiting position
     */
    core::bitboard_t end = 0;

    /**
     * Not used most of the time
     */
    core::Piece promotion = NONE;

    /**
     * Not used most of the time.
     *
     * Castle king side = 1
     * Castle queen's side = 1
     */
    std::int8_t castle = 0;
};

/**
 * Board player is a wrapper around the Board that provides game management and
 * a higher level control of the game. Management such as playing moves,
 * checking wins are available
 */
class BoardPlayer {
public:
    BoardPlayer();

    ~BoardPlayer();

private:
    bool _is_move_possible(Move const& move);

    static Move _generate_move(std::string const& start,
                                      std::string const& end,
                                      core::Piece promotion = NONE,
                                      std::uint8_t castle = 0);

    core::Board _board;
};

} // namespace core