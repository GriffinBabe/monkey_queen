#include <core/fen.hpp>
#include <core/piece.hpp>
#include <core/board.hpp>
#include <sstream>

std::string core::to_fen(const Board& board)
{
    std::stringstream stream;

    int cols = board.cols();
    int rows = board.rows();

    auto* board_array = board.board();
    for (int row = 0; row < rows; row++) {
        int empty_cell_counter = 0;
        for (int col = 0; col < cols; col++) {
            uchar piece = board_array[row * cols + col];
            if (piece == core::Piece::NONE) {
                empty_cell_counter++; // increment empty cell
            }
            else {
                // piece encountered, flush empty cell counter
                if (empty_cell_counter > 0) {
                    stream << empty_cell_counter;
                    empty_cell_counter = 0;
                }
                if (piece & Piece::WHITE & Piece::MONKEY) {
                    stream << "M";
                }
                else if (piece & Piece::WHITE & Piece::QUEEN) {
                    stream << "Q";
                }
                else if (piece & Piece::BLACK & Piece::MONKEY) {
                    stream << "m";
                }
                else if (piece & Piece::BLACK & Piece::QUEEN) {
                    stream << "q";
                }
            }
        }
        // end of row, flush empty cell counter
        if (empty_cell_counter > 0) {
            stream << empty_cell_counter;
            empty_cell_counter = 0;
        }
        if (row != rows - 1) {
            stream << "/";
        }
    }
    stream << " ";
    uchar playing = board.playing();
    if (playing == Team::WHITE_T) {
        stream << "w ";
    }
    else if (playing == Team::BLACK_T) {
        stream << "b ";
    }

    // TODO finish turn indication

    return stream.str();
}