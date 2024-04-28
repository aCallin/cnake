#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "resources.h"

struct background {
    TTF_Font *font;
    SDL_Color text_color;
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect text_rect;
};

void background_load(struct background *background, resources resources, SDL_Renderer *renderer, int internal_width);
void background_draw(struct background *background, SDL_Renderer *renderer, int tile_size, int tile_dimension);
void background_unload(struct background *background, resources resources);

#endif
