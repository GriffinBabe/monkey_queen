#include "core/board.hpp"
#include <memory>

core::Board::Board()
{
    clear_board();
}

core::Board::~Board()
{
}

void core::Board::clear_board()
{
    std::memset(&_board, 0, sizeof(std::uint64_t) * 14);
}
