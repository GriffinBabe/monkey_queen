#pragma once
#include <core/observer.hpp>
#include <core/piece.hpp>

namespace core {

using uchar = unsigned char;

class Board : public Observable {
public:

    Board(int cols, int rows);


    [[nodiscard]] const uchar* board() const;

    [[nodiscard]] uchar* get_board();

    [[nodiscard]] uchar playing() const;

    [[nodiscard]] int cols() const;

    [[nodiscard]] int rows() const;

    [[nodiscard]] int turn() const;

private:
    int _cols = 0;
    int _rows = 0;

    int _turn = 0;

    uchar _playing = Team::WHITE_T;


    std::unique_ptr<uchar> _board = nullptr;
};


}