#include <vector>
#include <map>
#include <SDL.h>

#pragma once

namespace gui {

class TextureManager {
public:
    TextureManager();

    ~TextureManager();

    bool init(SDL_Renderer* renderer);

    SDL_Texture* get_texture(const char* name);

private:
    std::map<std::string, SDL_Texture*> _textures;

    SDL_Texture* load(const char* name, SDL_Renderer* renderer);

    // hard coded textures and names
    bool load_textures(SDL_Renderer* renderer);

    void destroy();
};
}