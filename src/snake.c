#include "snake.h"

#define MOVE_FRAMES 20

void snake_load(struct snake *const s, resources const resources, SDL_Renderer *const renderer, const int tile_dimension) {
    s->body_tiles = malloc(tile_dimension * tile_dimension * sizeof(SDL_Point));
    if (s->body_tiles == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "load_snake(): malloc body_tiles returned NULL");
        return;
    }
    s->body_tiles[0].x = 4;
    s->body_tiles[0].y = tile_dimension / 2;
    s->body_tiles[1].x = 3;
    s->body_tiles[1].y = tile_dimension / 2;
    s->body_tiles[2].x = 2;
    s->body_tiles[2].y = tile_dimension / 2;
    s->body_tiles_length = 3;

    s->keyboard_state = SDL_GetKeyboardState(NULL);
    s->move_direction.x = 0;
    s->move_direction.y = 0;
    s->last_move_direction.x = 2;
    s->last_move_direction.y = 2;
    s->started_moving = SDL_FALSE;
    s->elapsed_move_frames = MOVE_FRAMES;
    s->last_tail_tile.x = 0;
    s->last_tail_tile.y = 0;
    s->collided = SDL_FALSE;
}

void snake_update(struct snake *const s, const int tile_dimension) {
    // Don't start moving until D is pressed for the first time
    if (!s->started_moving && s->keyboard_state[SDL_SCANCODE_D])
        s->started_moving = SDL_TRUE;

    // Gather movement input
    const SDL_Point backup_move_direction = s->move_direction;
    if (s->keyboard_state[SDL_SCANCODE_W]) {
        s->move_direction.x = 0;
        s->move_direction.y = -1;
    } else if (s->keyboard_state[SDL_SCANCODE_A]) {
        s->move_direction.x = -1;
        s->move_direction.y = 0;
    } else if (s->keyboard_state[SDL_SCANCODE_S]) {
        s->move_direction.x = 0;
        s->move_direction.y = 1;
    } else if (s->keyboard_state[SDL_SCANCODE_D]) {
        s->move_direction.x = 1;
        s->move_direction.y = 0;
    }
    if (s->move_direction.x == -s->last_move_direction.x || s->move_direction.y == -s->last_move_direction.y)
        s->move_direction = backup_move_direction;

    // Apply movement
    if (s->started_moving) {
        s->elapsed_move_frames++;
        if (s->elapsed_move_frames >= MOVE_FRAMES) {
            s->last_tail_tile.x = s->body_tiles[s->body_tiles_length - 1].x;
            s->last_tail_tile.y = s->body_tiles[s->body_tiles_length - 1].y;
            for (int i = s->body_tiles_length - 1; i >= 1; i--) {
                s->body_tiles[i].x = s->body_tiles[i - 1].x;
                s->body_tiles[i].y = s->body_tiles[i - 1].y;
            }
            s->body_tiles[0].x += s->move_direction.x;
            s->body_tiles[0].y += s->move_direction.y;
            s->last_move_direction = s->move_direction;
            s->elapsed_move_frames = 0;

            // Check collision after movement
            if (s->body_tiles[0].x < 0 || s->body_tiles[0].x >= tile_dimension || s->body_tiles[0].y < 0 || s->body_tiles[0].y >= tile_dimension)
                s->collided = SDL_TRUE;
            for (int i = 1; i < s->body_tiles_length; i++) {
                if (s->body_tiles[0].x == s->body_tiles[i].x && s->body_tiles[0].y == s->body_tiles[i].y)
                    s->collided = SDL_TRUE;
            }
        }
    }
}

void snake_draw(struct snake *const s, SDL_Renderer *const renderer, const int tile_size) {
    for (int i = 0; i < s->body_tiles_length; i++) {
        SDL_SetRenderDrawColor(renderer, 128, 93, 228, SDL_ALPHA_OPAQUE);
        SDL_Rect body_rect = {s->body_tiles[i].x * tile_size, s->body_tiles[i].y * tile_size, tile_size, tile_size};
        SDL_RenderFillRect(renderer, &body_rect);
    }
}

void snake_unload(struct snake *const s, resources const resources) {
    free(s->body_tiles);
}

SDL_bool snake_collided(struct snake *const s) {
    return s->collided;
}

SDL_Point snake_head_tile(struct snake *const s) {
    return s->body_tiles[0];
}

SDL_Point *snake_all_tiles(struct snake *const s, int *const length) {
    *length = s->body_tiles_length;
    return s->body_tiles;
}

void snake_grow(struct snake *const s) {
    s->body_tiles[s->body_tiles_length].x = s->last_tail_tile.x;
    s->body_tiles[s->body_tiles_length].y = s->last_tail_tile.y;
    s->body_tiles_length++;
}
