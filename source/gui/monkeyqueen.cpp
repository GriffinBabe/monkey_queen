#include <gui/window.hpp>
#include <core/board.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    core::Board board(8, 8);

    gui::Window window;
    window.init();

    window.set_board_size(board.cols(), board.rows());

    // GUI for-loop
    const float frame_rate = 5.0f; // 60 FPS
    int end = 0;
    while (true) {
        int begin = SDL_GetTicks();
        float delta = begin - end;

        if (delta > 1000.0f/frame_rate) {
            window.clear();

            end = begin;

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                bool keep = window.on_event(event);
                if (!keep) return 0;
            }

            window.draw(0.0f);
        }
        else {
            SDL_Delay(1000.0f/frame_rate - delta);
        }
    }
}
