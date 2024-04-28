#include "game_scene_common.h"

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
    snake_update(&pd->snake);
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
