#ifndef SDL_UTIL_H
#define SDL_UTIL_H

#include "SDL.h"
#include "SDL_ttf.h"

void render_text(
    TTF_Font *font, 
    const char *text, 
    SDL_Color color, 
    SDL_Renderer *renderer, 
    SDL_Surface **surface, 
    SDL_Texture **texture, 
    int *width, 
    int *height
);

#endif
