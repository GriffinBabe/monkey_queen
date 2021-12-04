#include "core/board_player.hpp"

core::BoardPlayer::BoardPlayer()
{
}

core::BoardPlayer::~BoardPlayer()
{
}

bool core::BoardPlayer::_is_move_possible(const core::Move& move)
{
    // Checks if the move is possible. There are many checks to perform.

    // 1. Is the piece of the current playing player?

    // 2. Is the destination available?

    // 3. If not horse, it the path clear?

    // TODO: Simulate the in a copy and check if the king is attacked after this.

    return true;
}

core::Move core::BoardPlayer::_generate_move(const std::string& start,
                                                   const std::string& end,
                                                   core::Piece promotion,
                                                   std::uint8_t castle)
{
    Move move;
    if (start.length() != 2 || end.length() != 2) {
        throw std::runtime_error(
            "Start and end positions must be of length 2, got " + start
            + " and " + end + ".");
    }
    std::int8_t start_index =
        util::get_index_from_position(start[0], start[1]);
    std::int8_t end_index = util::get_index_from_position(end[0], end[0]);
    if (start_index == -1 || end_index == -1) {
        throw std::runtime_error("Couldn't parse start and end positions. ");
    }

    move.start = core::UNIT << (std::uint8_t) start_index;
    move.end = core::UNIT << (std::uint8_t) end_index;
    move.promotion = promotion;
    move.castle = castle;

    return move;
}
