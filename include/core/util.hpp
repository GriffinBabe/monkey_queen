#pragma once

#include <cstdint>
#include "core/board.hpp"

namespace util {

/**
 * Converts a chess position into its bitboard index.
 * For example a8 -> 0, b8 -> 1
 * @return
 */
[[nodiscard]] std::int8_t get_index_from_position(char file, char rank);

/**
 * Prints a bit board in the standard output, for example.
 *
 * bitboard: 0x0000000000000001 ->
 *  8  1  .  .  .  .  .  .  .
 *  7  .  .  .  .  .  .  .  .
 *  6  .  .  .  .  .  .  .  .
 *  5  .  .  .  .  .  .  .  .
 *  4  .  .  .  .  .  .  .  .
 *  3  .  .  .  .  .  .  .  .
 *  2  .  .  .  .  .  .  .  .
 *  1  .  .  .  .  .  .  .  .
 *     a  b  c  d  e  f  g  h
 *
 * @param board the bitboard to print in stdout
 */
void print_bitboard(core::bitboard_t board);

}