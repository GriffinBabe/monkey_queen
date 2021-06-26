#pragma once
#include <core/observer.hpp>
#include <core/piece.hpp>

namespace core {

using uchar = unsigned char;

class Board : public Observable {
public:
    Board(int cols,
          int rows,
          int stack = 8,
          int turn = 0,
          uchar playing = WHITE_T);

    [[nodiscard]] const uchar* board() const;

    [[nodiscard]] uchar* get_board();

    [[nodiscard]] uchar playing() const;

    [[nodiscard]] int cols() const;

    [[nodiscard]] int rows() const;

    [[nodiscard]] int turn() const;

    [[nodiscard]] int stack(core::Team team) const;

    void set_stack(int stack, core::Team team);

    void set_board(uchar* board, size_t size);

private:
    int _white_queen_stack = 0;

    int _black_queen_stack = 0;

    int _cols = 0;

    int _rows = 0;

    int _turn = 0;

    uchar _playing = Team::WHITE_T;

    std::unique_ptr<uchar> _board = nullptr;
};

} // namespace core