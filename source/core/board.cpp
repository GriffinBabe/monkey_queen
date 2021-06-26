#include <core/board.hpp>

core::Board::Board(int cols, int rows, int stack, int turn, uchar playing)
    : _cols(cols),
      _rows(rows),
      _white_queen_stack(stack),
      _black_queen_stack(stack),
      _turn(turn),
      _playing(playing)
{
    _board = std::unique_ptr<uchar>(new uchar[_cols * _rows]);
    memset(_board.get(), 0, sizeof(uchar) * _cols * _rows);
}

int core::Board::cols() const
{
    return _cols;
}

int core::Board::rows() const
{
    return _rows;
}
const core::uchar* core::Board::board() const
{
    return _board.get();
}

core::uchar* core::Board::get_board()
{
    return _board.get();
}

core::uchar core::Board::playing() const
{
    return _playing;
}

int core::Board::turn() const
{
    return _turn;
}

int core::Board::stack(core::Team team) const
{
    if (team == WHITE_T) return _white_queen_stack;
    else return _black_queen_stack;
}

void core::Board::set_stack(int stack, core::Team team)
{
    if (team == WHITE_T) {
        _white_queen_stack = stack;
    }
    else {
        _black_queen_stack = stack;
    }
}

void core::Board::set_board(uchar* board, size_t size)
{
    if (size != _cols * _rows) {
        throw std::runtime_error("Cannot import board with different size.");
    }
    memcpy(_board.get(), board, size);
}
