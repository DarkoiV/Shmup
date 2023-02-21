#include "Gng2D/core/functions.hpp"
#include <SDL2/SDL.h>

void Gng2D::requestQuit()
{
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
}
