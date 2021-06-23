#pragma once

#include <SDL.h>
#include <vector>
#include <gui/drawinstance.hpp>
#include <gui/texture_manager.hpp>

namespace gui {
const int base_width = 1200;
const int base_height = 800;

class Window {
public:

    Window(int width=base_width, int height=base_height);

    bool init();

    void clear();

    void draw();

    bool destroy();

private:

    SDL_Renderer* _renderer = nullptr;
    SDL_Window* _window = nullptr;

    TextureManager _texture_manager;

    std::vector<std::shared_ptr<DrawInstance>> _instance;

    int _width = 0;
    int _height = 0;
};

}