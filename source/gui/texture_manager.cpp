#include <SDL_image.h>
#include <gui/texture_manager.hpp>
#include <iostream>

gui::TextureManager::TextureManager()
{
}

bool gui::TextureManager::load_textures(SDL_Renderer* renderer)
{
    constexpr char* white_monkey_path = "./assets/sprites/white_monkey.png";
    constexpr char* black_monkey_path = "./assets/sprites/black_monkey.png";

    constexpr char* white_queen_path = "./assets/sprites/white_queen.png";
    constexpr char* black_queen_path = "./assets/sprites/black_queen.png";

    SDL_Texture* loaded;

    if (!(loaded = load(white_monkey_path, renderer)))
        return false;
    _textures.insert({std::string("white_monkey"), loaded});

    if (!(loaded = load(black_monkey_path, renderer)))
        return false;
    _textures.insert({std::string("black_monkey"), loaded});

    if (!(loaded = load(white_queen_path, renderer)))
        return false;
    _textures.insert({std::string("white_queen"), loaded});

    if (!(loaded = load(black_queen_path, renderer)))
        return false;
    _textures.insert({std::string("black_queen"), loaded});

    return true;
}

SDL_Texture* gui::TextureManager::load(const char* name, SDL_Renderer* renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, name);
    return texture;
}

bool gui::TextureManager::init(SDL_Renderer* renderer)
{
    return load_textures(renderer);
}

void gui::TextureManager::destroy()
{
    // iterates over all textures and destroys them
    for (const auto& [name, texture] : _textures) {
        SDL_DestroyTexture(texture);
    }
}

gui::TextureManager::~TextureManager()
{
    destroy();
}

SDL_Texture* gui::TextureManager::get_texture(const char* name)
{
    return _textures.at(name);
}
