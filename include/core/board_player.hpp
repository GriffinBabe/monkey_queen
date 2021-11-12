#pragma once
#include "core/board.hpp"
#include "core/fen.hpp"


namespace core {

struct Move {
    /**
     * Starting position
     */
    std::uint8_t start_index = 0;

    /**
     * Exiting position
     */
    std::uint8_t stop_index = 0;

    /**
     * Not used most of the time
     */
    core::Piece promotion = NONE;

    /**
     * Not used most of the time
     */
    core::Piece castle = NONE;
};

/**
 * Board player is a wrapper around the Board that provides game management and
 * a higher level control of the game. Management such as playing moves, checking
 * wins are available
 */
class BoardPlayer {
public:
    BoardPlayer();

    ~BoardPlayer();

private:

    bool is_move_possible();

    core::Board _board;
};

}