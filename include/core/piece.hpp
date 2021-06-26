#pragma once

namespace core {

using uchar = unsigned char;

// can be encoded in 1 char
enum Piece {
    NONE = 0,   // 00000000
    MONKEY = 1, // 00000001
    QUEEN = 2,  // 00000010
    WHITE = 4,  // 00000100
    BLACK = 8,  // 00001000
};

enum Team { WHITE_T = 0, BLACK_T = 1 };

using CoordInt = char;

struct BoardCoord {
    CoordInt x = 0;
    CoordInt y = 0;
};

/**
 * Checks wherever a piece has a certain color and a certain type.
 * @param piece, the actual piece (color + type)
 * @param type, the type (Monkey or Queen)
 * @param color, the color (Black or white)
 * @return true if match, false otherwise.
 */
inline bool piece_is(uchar piece, uchar type, uchar color) {
    return (piece & type) && (piece & color);
}

} // namespace core