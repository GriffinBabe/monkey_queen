#include <core/board.hpp>
#include <core/fen.hpp>
#include <core/piece.hpp>
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
                if (piece_is(piece, Piece::MONKEY, Piece::WHITE)) {
                    stream << "M";
                }
                else if (piece_is(piece, Piece::QUEEN, Piece::WHITE)) {
                    stream << "Q";
                }
                else if (piece_is(piece, Piece::MONKEY, Piece::BLACK)) {
                    stream << "m";
                }
                else if (piece_is(piece, Piece::QUEEN, Piece::BLACK)) {
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

    stream << "- " << board.turn() << " - " << board.stack(WHITE_T) << " - "
           << board.stack(BLACK_T);

    return stream.str();
}

core::Board core::from_fen(const std::string& fen)
{
    std::vector<uchar> pieces;

    // counts the number of rows
    size_t rows = std::count(fen.begin(), fen.end(), '/') + 1;

    auto itr = fen.begin();

    for (itr; itr != fen.end() && *itr != ' '; itr++) {
        char piece = *itr;
        switch (piece) {
        case 'M':
            pieces.push_back(WHITE | MONKEY);
            break;
        case 'm':
            pieces.push_back(BLACK | MONKEY);
            break;
        case 'Q':
            pieces.push_back(WHITE | QUEEN);
            break;
        case 'q':
            pieces.push_back(BLACK | QUEEN);
            break;
        case '/':
            continue;
        default:
            // TODO can only read for columns white 9 columns at max
            int empty_cells = piece - '0';
            for (int i = 0; i < empty_cells; i++)
                pieces.push_back(core::Piece::NONE);
        }
    }

    size_t cols = pieces.size() / rows;
    uchar playing;

    itr++; // skip white space

    if (*itr == 'w') {
        playing = WHITE_T;
    }
    else {
        playing = BLACK_T;
    }

    itr += 4; // go to turn count

    int turn_count = *itr - '0';

    itr += 4; // go to white stack

    int white_stack = *itr - '0';

    itr += 4; // go to black stack

    int black_stack = *itr - '0';

    Board board(cols, rows, 0, turn_count, playing);
    board.set_stack(white_stack, WHITE_T);
    board.set_stack(black_stack, BLACK_T);
    board.set_board(pieces.data(), cols * rows);

    return board;
}