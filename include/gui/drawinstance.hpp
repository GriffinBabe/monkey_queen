#pragma once

#include <string>
#include <SDL.h>
#include <gui/texture_manager.hpp>
#include <core/piece.hpp>

namespace gui {

std::string get_piece_name(core::Piece piece);

enum PieceStatus {
    STILL, MOVING, DRAGGED
};

class DrawInstance {

public:
    DrawInstance(std::string name);

    virtual void draw(SDL_Renderer* renderer, TextureManager const& manager) = 0;

private:
    std::string _texture_name;

    int x = 0;
    int y = 0;
};

class PieceInstance : DrawInstance {
public:
    PieceInstance(core::Piece piece);

    void draw(SDL_Renderer* renderer, const TextureManager& manager) override;

private:
    core::Piece _piece;
};


}