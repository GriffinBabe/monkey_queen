#include <gui/drawinstance.hpp>
#include <iostream>

std::string gui::get_piece_name(core::Piece piece)
{
    if (piece & core::Piece::MONKEY & core::Piece::WHITE) {
        return "white_monkey";
    }
    else if (piece & core::Piece::MONKEY & core::Piece::BLACK) {
        return "black_monkey";
    }
    else if (piece & core::Piece::QUEEN & core::Piece::WHITE) {
        return "white_queen";
    }
    else if (piece & core::Piece::QUEEN & core::Piece::BLACK) {
        return "black_queen";
    }
    return ""; // error
}

gui::DrawInstance::DrawInstance(std::string name)
    : _texture_name(name)
{
}

//------------------------------------------------------------------------------
// Piece Class definitions
//------------------------------------------------------------------------------

gui::PieceInstance::PieceInstance(core::Piece piece)
    : DrawInstance(get_piece_name(piece))
{
}

void gui::PieceInstance::draw(SDL_Renderer* renderer,
                              const gui::TextureManager& manager)
{
    std::cout << "Draw piece" << std::endl;
}

void gui::PieceInstance::update(core::Observable* observer,
                                core::GameEvent& event)
{
    // TODO implement
}
