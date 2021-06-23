#include <gui/window.hpp>
#include <core/piece.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    char piece = core::Piece::MONKEY | core::Piece::WHITE;

    std::cout << piece << std::endl;
    std::cout << sizeof(core::Piece) << std::endl;


    gui::Window window;
    window.init();

    while (true) {
        window.clear();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                window.destroy();
                return 0;
            default:
                break;
            }
        }

        window.draw();
    }
}
