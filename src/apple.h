#ifndef APPLE_H
#define APPLE_H

#include "SDL.h"
#include "resources.h"

struct apple {
    SDL_Texture *texture;
    SDL_Point texture_size;
    SDL_Point tile;
};

void apple_load(struct apple *apple, resources resources, SDL_Renderer *renderer, int tile_dimension);
void apple_draw(const struct apple *apple, SDL_Renderer *renderer, int tile_size);
void apple_unload(const struct apple *apple, resources resources);

SDL_Point apple_get_tile(const struct apple *apple);
void apple_set_tile(struct apple *apple, SDL_Point tile);

#endif
