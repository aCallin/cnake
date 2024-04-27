#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include "resources.h"

struct snake {
    SDL_Point *body_tiles;
    int body_tiles_length;

    const Uint8 *keyboard_state;
    SDL_Point move_direction;
    SDL_Point last_move_direction;
    SDL_bool started_moving;
    int elapsed_move_frames;
};

void snake_load(struct snake *s, resources resources, SDL_Renderer *renderer, int tile_dimension);
void snake_update(struct snake *s);
void snake_draw(struct snake *s, SDL_Renderer *renderer, int tile_size);
void snake_unload(struct snake *s, resources resources);

#endif
