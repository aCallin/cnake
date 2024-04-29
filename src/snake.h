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
    SDL_Point last_tail_tile;
    SDL_bool collided;
};

void snake_load(struct snake *s, resources resources, SDL_Renderer *renderer, int tile_dimension);
void snake_update(struct snake *s, int tile_dimension);
void snake_draw(struct snake *s, SDL_Renderer *renderer, int tile_size);
void snake_unload(struct snake *s, resources resources);

SDL_bool snake_collided(struct snake *s);
SDL_Point snake_head_tile(struct snake *s);
SDL_Point *snake_all_tiles(struct snake *s, int *length);
void snake_grow(struct snake *s);

#endif
