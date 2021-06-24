#include <core/board.hpp>

core::Board::Board(int cols, int rows)
    : _cols(cols), _rows(rows)
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
