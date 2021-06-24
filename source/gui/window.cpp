#include <gui/window.hpp>
#include <iostream>

gui::Window::Window(int width, int height) : _width(width), _height(height)
{
}

bool gui::Window::init()
{
    int render_flags, window_flags;

    render_flags = SDL_RENDERER_ACCELERATED;

    window_flags = SDL_WINDOW_RESIZABLE;

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

    // minimum window size
    SDL_SetWindowMinimumSize(_window, min_width, min_height);

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
    SDL_SetRenderDrawColor(_renderer, color_beige.r, color_beige.g, color_beige.b, 255);
    SDL_RenderClear(_renderer);
}

void gui::Window::draw(float delta)
{

    // 1. Draw board
    if (_board_rows != 0 && _board_cols != 0) draw_board();

    // 2. Draw column
    draw_column();

    // 3. Draw column elements

    // 4. Present final draw
    SDL_RenderPresent(_renderer);
}

bool gui::Window::destroy()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

bool gui::Window::on_event(SDL_Event const& event)
{
    switch (event.type) {
    case SDL_QUIT:
        destroy();
        return false;
    case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            on_resize();
        }
        break;
    default:
        break;
    }

    return true;
}

void gui::Window::on_resize()
{
    // update window size information
    int width, height;
    SDL_GetWindowSize(_window, &width, &height);
    _width = width;
    _height = _width * board_width_ratio;

    // keep window ratio
    SDL_SetWindowSize(_window, _width, _height);
}

void gui::Window::set_board_size(int cols, int rows)
{
    _board_cols = cols;
    _board_rows = rows;
}

void gui::Window::draw_board()
{
    int board_width_px = _width * board_width_ratio;
    int board_height_px = _height * board_height_ratio;

    int column_px = board_width_px / _board_cols;
    int row_px = board_height_px / _board_rows;

    // set brown color for renderer
    SDL_SetRenderDrawColor(_renderer, color_brown.r, color_brown.g, color_brown.b, 255);

    for (int col = 0; col < _board_cols; col++) {
        for (int row = 0; row < _board_rows; row++) {
            if ((col + row) % 2 == 1) {
                SDL_Rect rect {column_px * col, row_px * row, column_px, row_px};
                SDL_RenderFillRect(_renderer, &rect);
            }
        }
    }
}

void gui::Window::draw_column()
{
    int board_width_px = _width * board_width_ratio;

    SDL_SetRenderDrawColor(_renderer, color_blue.r, color_blue.g, color_blue.b, 255);
    SDL_Rect rect = {board_width_px, 0, (_width - board_width_px), _height};
    SDL_RenderFillRect(_renderer, &rect);
}

void gui::Window::update(core::Observable* observer, core::GameEvent& event)
{
    // TODO implement
}

