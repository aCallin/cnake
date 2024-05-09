#include "game_scene_common.h"

#include <string.h>
#include "background.h"
#include "snake.h"
#include "apple.h"

#define TILE_SIZE 40

struct data {
    int tile_dimension;
    int score;
    
    struct background background;
    struct snake snake;
    struct apple apple;
};

static SDL_Point generate_next_apple_tile(const int tile_dimension, struct snake *const snake) {
    const int num_tiles = tile_dimension * tile_dimension;

    struct possible_tile_entry {
        SDL_Point tile;
        SDL_bool marked;
    };

    // Create set of possible tiles for the apple
    struct possible_tile_entry *const possible_tile_entries = malloc(num_tiles * sizeof(struct possible_tile_entry));
    for (int i = 0; i < num_tiles; i++) {
        possible_tile_entries[i].tile.x = i % tile_dimension;
        possible_tile_entries[i].tile.y = i / tile_dimension;
        possible_tile_entries[i].marked = SDL_FALSE;
    }
    int possible_tile_entries_length = num_tiles;

    // Mark tiles that are occupied by the snake
    int occupied_tiles_length;
    const SDL_Point *const occupied_tiles = snake_all_tiles(snake, &occupied_tiles_length);
    for (int i = 0; i < occupied_tiles_length; i++) {
        const int occupied_tile_index = occupied_tiles[i].x + occupied_tiles[i].y * tile_dimension;
        possible_tile_entries[occupied_tile_index].marked = SDL_TRUE;
    }

    // "Remove" the tiles that are marked
    int copy_behind_offset = 0;
    for (int i = 0; i < num_tiles; i++) {
        if (possible_tile_entries[i].marked == SDL_TRUE) {
            possible_tile_entries_length--;
            copy_behind_offset++;
        } else if (copy_behind_offset != 0) {
            possible_tile_entries[i - copy_behind_offset].tile = possible_tile_entries[i].tile;
            possible_tile_entries[i - copy_behind_offset].marked = SDL_FALSE;
        }
    }

    // Choose a random tile from what remains of possible tiles
    const int random_index = rand() % possible_tile_entries_length;
    SDL_Point tile;
    tile.x = possible_tile_entries[random_index].tile.x;
    tile.y = possible_tile_entries[random_index].tile.y;
    free(possible_tile_entries);
    return tile;
}

void load_play_scene(struct game_container *gc) {
    SDL_Log("Start load play scene");

    gc->scene.data = malloc(sizeof(struct data));
    struct data *const pd = (struct data *)gc->scene.data;
    pd->tile_dimension = gc->internal_width / TILE_SIZE;
    pd->score = 0;
    background_load(&pd->background, gc->resources, gc->renderer, gc->internal_width);
    snake_load(&pd->snake, gc->resources, gc->renderer, pd->tile_dimension);
    apple_load(&pd->apple, gc->resources, gc->renderer, pd->tile_dimension);

    SDL_Log("Load play scene done");
}

void update_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;

    if (!snake_collided(&pd->snake)) {
        snake_update(&pd->snake, pd->tile_dimension);
        if (!snake_collided(&pd->snake)) {
            const SDL_Point head_tile = snake_head_tile(&pd->snake);
            const SDL_Point apple_tile = apple_get_tile(&pd->apple);
            if (head_tile.x == apple_tile.x && head_tile.y == apple_tile.y) {
                SDL_Log("Snake ate apple");
                snake_grow(&pd->snake);
                SDL_Point next_apple_tile = generate_next_apple_tile(pd->tile_dimension, &pd->snake);
                apple_set_tile(&pd->apple, next_apple_tile);
            }
        }
    }
}

void draw_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;
    background_draw(&pd->background, gc->renderer, TILE_SIZE, pd->tile_dimension);
    snake_draw(&pd->snake, gc->renderer, TILE_SIZE);
    apple_draw(&pd->apple, gc->renderer, TILE_SIZE);
}

void unload_play_scene(struct game_container *gc) {
    SDL_Log("Start unload play scene");

    struct data *const pd = (struct data *)gc->scene.data;

    apple_unload(&pd->apple, gc->resources);
    snake_unload(&pd->snake, gc->resources);
    background_unload(&pd->background, gc->resources);
    free(gc->scene.data);

    SDL_Log("Unload play scene done");
}
