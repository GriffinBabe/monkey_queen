#include "core/util.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

const std::vector<char> rank_array = {'1', '2', '3', '4', '5', '6', '7', '8'};
const std::vector<char> file_array = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

std::int8_t util::get_index_from_position(char file, char rank)
{
    if ((file >= 'a') && (file <= 'h') && ((rank >= '1') && (rank <= '8'))) {
        int file_index = file - 96;
        int rank_index = rank - 48;

        return (8 - rank_index) * 8 + (file_index - 1);
    }
    else
        return -1;
}

void util::print_bitboard(core::bitboard_t board)
{
    std::stringstream ss;
    for (int rank = 7; rank >= 0; rank--) {
        ss << rank_array[rank] << " ";
        for (int file = 0; file < 8; file++) {
            std::uint8_t index_position =
                get_index_from_position(file_array[file], rank_array[rank]);
            std::uint64_t mask = core::UNIT << index_position;
            if (board & mask) {
                ss << "1  ";
            } else ss << ".  ";
        }
        ss << "\n";
    }
    ss << "  ";
    for (int file = 0; file < 8; file++) {
        ss << file_array[file] << "  ";
    }

    std::cout << ss.str() << std::endl;
}