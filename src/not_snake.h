#ifndef NOT_SNAKE_H
#define NOT_SNAKE_H

#include "SDL.h"
#include "resources.h"

struct not_snake {
    SDL_Texture *apple_texture;
    SDL_Rect apple_rect;
};

void load_not_snake(struct not_snake *ns, resources resources, SDL_Renderer *renderer, int tile_size, int tile_dimension);
void draw_not_snake(struct not_snake *ns, SDL_Renderer *renderer, int tile_size, int tile_dimension);
void unload_not_snake(struct not_snake *ns, resources resources);

#endif
