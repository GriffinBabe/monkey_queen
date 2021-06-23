add_library(core SHARED
        core/piece.cpp)

add_library(gui SHARED
        gui/window.cpp
        gui/drawinstance.cpp
        gui/texture_manager.cpp)

target_link_libraries(gui PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} core)

add_executable(monkeyqueen
        gui/monkeyqueen.cpp)

target_link_libraries(monkeyqueen PUBLIC gui core)

