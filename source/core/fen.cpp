#include "core/fen.hpp"
#include "core/util.hpp"
#include <vector>

// StackOverflow
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(std::string input, const std::string& delimiter)
{
    std::vector<std::string> splittedStrings = {};
    size_t pos = 0;

    while ((pos = input.find(delimiter)) != std::string::npos) {
        std::string token = input.substr(0, pos);
        if (token.length() > 0)
            splittedStrings.push_back(token);
        input.erase(0, pos + delimiter.length());
    }

    if (input.length() > 0)
        splittedStrings.push_back(input);
    return splittedStrings;
}

// http://www.fam-petzke.de/cp_fen_en.shtml
core::Board core::from_fen(const std::string& fen)
{
    core::Board board;
    auto str_list = split(fen, " ");
    std::uint8_t board_idx = 0;
    int str_idx = 0;

    auto board_notation = str_list.at(0);

    // There should be 6 members in the FEN notation
    // 1. Board, 2. Player to Move, 3. Possible castles, 4. Possible en passant
    // 5. Black turn count 6. White turn count
    if (str_list.size() < 6) {
        throw std::runtime_error(
            "Invalid FEN expression (Not enough arguments): " + fen);
    }
    if (str_list.size() > 6) {
        throw std::runtime_error("Invalid FEN expression (Too many arguments): "
                                 + fen);
    }

    // Sets up the piece positions
    while (board_idx < 64 && str_idx < board_notation.length()) {
        auto letter = board_notation.at(str_idx++); // get letter and increment
        switch (letter) {
        case 'p':
            board.set_piece(UNIT << board_idx, PAWN, BLACK);
            break;
        case 'r':
            board.set_piece(UNIT << board_idx, ROOK, BLACK);
            break;
        case 'n':
            board.set_piece(UNIT << board_idx, KNIGHT, BLACK);
            break;
        case 'b':
            board.set_piece(UNIT << board_idx, BISHOP, BLACK);
            break;
        case 'q':
            board.set_piece(UNIT << board_idx, QUEEN, BLACK);
            break;
        case 'k':
            board.set_piece(UNIT << board_idx, KING, BLACK);
            break;
        case 'P':
            board.set_piece(UNIT << board_idx, PAWN, WHITE);
            break;
        case 'R':
            board.set_piece(UNIT << board_idx, ROOK, WHITE);
            break;
        case 'N':
            board.set_piece(UNIT << board_idx, KNIGHT, WHITE);
            break;
        case 'B':
            board.set_piece(UNIT << board_idx, BISHOP, WHITE);
            break;
        case 'Q':
            board.set_piece(UNIT << board_idx, QUEEN, WHITE);
            break;
        case 'K':
            board.set_piece(UNIT << board_idx, KING, WHITE);
            break;
        case '/':
            board_idx--;
            break;
        case '1':
            break;
        case '2':
            board_idx++;
            break;
        case '3':
            board_idx += 2;
            break;
        case '4':
            board_idx += 3;
            break;
        case '5':
            board_idx += 4;
            break;
        case '6':
            board_idx += 5;
            break;
        case '7':
            board_idx += 6;
            break;
        case '8':
            board_idx += 7;
            break;
        default:
            throw std::runtime_error(
                "Invalid FEN expression (invalid piece name): " + fen);
        }
        board_idx++;
    }
    // check if all the cells where parsed
    if (board_idx != 64) {
        throw std::runtime_error("Invalid FEN expression (incomplete board): "
                                 + fen);
    }

    auto player_to_move = WHITE;
    auto str_to_move = str_list.at(1);

    if (str_to_move == "w") {
        player_to_move = WHITE;
    }
    else if (str_to_move == "b") {
        player_to_move = BLACK;
    }
    else {
        throw std::runtime_error(
            "Invalid FEN expression (invalid player to move): " + fen);
    }
    board.set_player_to_move(player_to_move);

    auto str_castles = str_list.at(2);
    for (auto character : str_castles) {
        if (character != '-' && character != 'K' && character != 'Q'
            && character != 'k' && character != 'q') {
            throw std::runtime_error(
                "Invalid FEN expression (invalid castle notation): " + fen);
        }
    }
    if (str_castles.find('K') != std::string::npos) {
        board.set_castle_white_king();
    }
    if (str_castles.find('Q') != std::string::npos) {
        board.set_castle_white_queen();
    }
    if (str_castles.find('k') != std::string::npos) {
        board.set_castle_black_king();
    }
    if (str_castles.find('q') != std::string::npos) {
        board.set_castle_black_queen();
    }

    auto en_passant_str = str_list.at(3);

    // parses en passant
    if (en_passant_str.length() != 2 && en_passant_str != "-") {
        throw std::runtime_error(
            "Invalid FEN expression (invalid en passant notation): " + fen);
    }
    else if (en_passant_str != "-") {
        std::int8_t en_passant_idx = util::get_index_from_position(
            en_passant_str.at(0), en_passant_str.at(1));
        if (en_passant_idx == -1) {
            throw std::runtime_error(
                "Invalid FEN expression (couldn't parse en passant notation): "
                + fen);
        }
        board.set_en_passant(UNIT << en_passant_idx);
    }

    // parses half turn clock
    auto half_turn_str = str_list.at(4);
    auto half_turn = std::stoi(half_turn_str);
    board.set_half_turn_clock(half_turn);

    // TODO check for errors

    // parsers full turn clock

    auto full_turn_str = str_list.at(5);
    auto full_turn = std::stoi(full_turn_str);
    board.set_full_turn_clock(full_turn);

    return board;
}

std::string core::to_fen(const Board& board)
{
    return std::string();
}