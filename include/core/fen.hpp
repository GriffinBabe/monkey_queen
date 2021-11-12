#pragma once
#include <string>

namespace core {

    // forward declaratin of board class
    class Board;

    /**
     * Transforms the given board array to a string of fen notation.
     * @return a string holding the fen notation of the current game state.
     */
    std::string to_fen(Board const& board);

    Board from_fen(std::string const& fen);


}