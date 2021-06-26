#pragma once
#include <string>

namespace core {

    // forward declaratin of board class
    class Board;

    /**
     * https://en.wikipedia.org/wiki/Forsyth–Edwards_Notation
     *
     * Transforms the given board array to a string of fen notation.
     * Here, the pieces are represented by:
     *  - m: Black monkey
     *  - q: Black queen
     *  - M: White monkey
     *  - Q: White queen
     *
     * @return a string holding the fen notation of the current game state.
     */
    std::string to_fen(Board const& board);

    Board from_fen(std::string const& fen);

}