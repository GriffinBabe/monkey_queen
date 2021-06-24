#pragma once

#include <SDL.h>
#include <vector>
#include <gui/drawinstance.hpp>
#include <gui/texture_manager.hpp>
#include <core/board.hpp>

namespace gui {

using uchar = unsigned char;

struct Color {
    uchar r = 0;
    uchar g = 0;
    uchar b = 0;
};

const int base_width = 1200;
const int base_height = 800;

const int min_width = 600;
const int min_height = 400;

const float board_width_ratio = 8.0f/12.0f;
const float board_height_ratio = 1.0f;

const Color color_beige = {240, 235, 221};
const Color color_brown = {163, 126, 73};
const Color color_blue = {152, 200, 237};

class Window : public core::Observer {
public:

    Window(int width=base_width, int height=base_height);

    bool init();

    void clear();

    void draw(float delta);

    bool destroy();

    bool on_event(SDL_Event const& event);

    void set_board_size(int cols, int rows);

    void update(core::Observable* observer, core::GameEvent& event) override;

private:

    void on_resize();

    void draw_board();

    void draw_column();

    SDL_Renderer* _renderer = nullptr;
    SDL_Window* _window = nullptr;

    TextureManager _texture_manager;

    std::vector<std::shared_ptr<DrawInstance>> _instance;

    int _width = 0;
    int _height = 0;

    int _board_cols = 0;
    int _board_rows = 0;
};

}