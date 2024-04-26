#include "snake.h"

#define MOVE_FRAMES 20

void load_snake(struct snake *const s, resources const resources, SDL_Renderer *const renderer, const int tile_dimension) {
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
}

void update_snake(struct snake *s) {
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
            for (int i = s->body_tiles_length - 1; i >= 1; i--) {
                s->body_tiles[i].x = s->body_tiles[i - 1].x;
                s->body_tiles[i].y = s->body_tiles[i - 1].y;
            }
            s->body_tiles[0].x += s->move_direction.x;
            s->body_tiles[0].y += s->move_direction.y;
            s->last_move_direction = s->move_direction;
            s->elapsed_move_frames = 0;
        }
    }
}

void draw_snake(struct snake *s, SDL_Renderer *const renderer, const int tile_size) {
    for (int i = 0; i < s->body_tiles_length; i++) {
        SDL_SetRenderDrawColor(renderer, 128, 93, 228, SDL_ALPHA_OPAQUE);
        SDL_Rect body_rect = {s->body_tiles[i].x * tile_size, s->body_tiles[i].y * tile_size, tile_size, tile_size};
        SDL_RenderFillRect(renderer, &body_rect);
    }
}

void unload_snake(struct snake *s, resources resources) {
    free(s->body_tiles);
}
