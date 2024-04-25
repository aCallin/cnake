#include "game_scene_common.h"

#include "not_snake.h"

#define TILE_SIZE 40

struct data {
    int tile_dimension;
};

void load_play_scene(struct game_container *gc) {
    SDL_Log("Start load play scene");

    gc->scene.data = malloc(sizeof(struct data));
    struct data *const pd = (struct data *)gc->scene.data;

    pd->tile_dimension = gc->internal_width / TILE_SIZE;

    SDL_Log("Load play scene done");
}

void update_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;
}

void draw_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;

    draw_tiles(gc->renderer, TILE_SIZE, pd->tile_dimension);
}

void unload_play_scene(struct game_container *gc) {
    SDL_Log("Start unload play scene");

    free(gc->scene.data);

    SDL_Log("Unload play scene done");
}
