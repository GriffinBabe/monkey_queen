#include <gui/window.hpp>
#include <iostream>

gui::Window::Window(int width, int height)
{
}

bool gui::Window::init()
{
    int render_flags, window_flags;

    render_flags = SDL_RENDERER_ACCELERATED;

    window_flags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // TODO add log
        std::cout << "Problem initializing video" << std::endl;
        return false;
    }

    _window = SDL_CreateWindow("Haraka game engine",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_CENTERED,
                               _width,
                               _height,
                               window_flags);

    if (!_window) {
        // TODO add log
        std::cout << "Problem initializing window." << std::endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer = SDL_CreateRenderer(_window, -1, render_flags);

    if (!_renderer) {
        // TODO add log
        std::cout << "Problem initializing renderer." << std::endl;
        return false;
    }

    // load all the game textures
    bool success = _texture_manager.init(_renderer);
    if (!success) {
        std::cout << "Problem while loading textures." << std::endl;
        return false;
    }

    return true;
}

void gui::Window::clear()
{
    SDL_SetRenderDrawColor(_renderer, 96, 128, 255, 255);
    SDL_RenderClear(_renderer);
}

void gui::Window::draw()
{
    SDL_RenderPresent(_renderer);
}

bool gui::Window::destroy()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

