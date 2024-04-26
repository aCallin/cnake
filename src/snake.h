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

void load_snake(struct snake *s, resources resources, SDL_Renderer *renderer, int tile_dimension);
void update_snake(struct snake *s);
void draw_snake(struct snake *s, SDL_Renderer *renderer, int tile_size);
void unload_snake(struct snake *s, resources resources);

#endif
