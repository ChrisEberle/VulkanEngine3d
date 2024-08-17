#include "sdl_utils.h"

// Define the global variable in the source file
bool SdlUtil::sdl_cursor_state = false;

void SdlUtil::sdl_set_cursor_game(SDL_Window* window) 
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(window, SDL_TRUE);
    SdlUtil::sdl_cursor_state = true;
}

void SdlUtil::sdl_set_cursor_free(SDL_Window* window) 
{
    
    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_SetWindowGrab(window, SDL_FALSE);
    SdlUtil::sdl_cursor_state = false;
}