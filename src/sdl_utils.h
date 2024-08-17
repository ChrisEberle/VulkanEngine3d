#pragma once

#include <SDL.h>

namespace SdlUtil
{
    extern bool sdl_cursor_state;
    // for locking and hiding the cursor to window
    void sdl_set_cursor_game(SDL_Window* window);
    void sdl_set_cursor_free(SDL_Window* window);
}