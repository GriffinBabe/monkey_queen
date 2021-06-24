#pragma once

namespace core {

// can be encoded in 1 char
enum Piece {
    NONE = 0,

    MONKEY = 1,
    QUEEN = 2,

    WHITE = 4,
    BLACK = 8,
};

enum Team {
    WHITE_T = 0,
    BLACK_T = 1
};

using CoordInt = char;

struct BoardCoord {
    CoordInt x = 0;
    CoordInt y = 0;
};

}