#include "game_scene_common.h"

#include "not_snake.h"
#include "snake.h"

#define TILE_SIZE 40

struct data {
    int tile_dimension;
    struct not_snake not_snake;
    struct snake snake;
};

void load_play_scene(struct game_container *gc) {
    SDL_Log("Start load play scene");

    gc->scene.data = malloc(sizeof(struct data));
    struct data *const pd = (struct data *)gc->scene.data;

    pd->tile_dimension = gc->internal_width / TILE_SIZE;
    load_not_snake(&pd->not_snake, gc->resources, gc->renderer, TILE_SIZE, pd->tile_dimension);
    load_snake(&pd->snake, gc->resources, gc->renderer, pd->tile_dimension);

    SDL_Log("Load play scene done");
}

void update_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;

    update_snake(&pd->snake);
}

void draw_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;

    draw_not_snake(&pd->not_snake, gc->renderer, TILE_SIZE, pd->tile_dimension);
    draw_snake(&pd->snake, gc->renderer, TILE_SIZE);
}

void unload_play_scene(struct game_container *gc) {
    SDL_Log("Start unload play scene");

    struct data *const pd = (struct data *)gc->scene.data;

    unload_snake(&pd->snake, gc->resources);
    unload_not_snake(&pd->not_snake, gc->resources);

    free(gc->scene.data);

    SDL_Log("Unload play scene done");
}
