#include "game_scene_common.h"

struct data {
    
};

void load_play_scene(struct game_container *gc) {
    SDL_Log("Start load play scene");

    gc->scene.data = malloc(sizeof(struct data));
    struct data *const pd = (struct data *)gc->scene.data;

    SDL_Log("Load play scene done");
}

void update_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;
}

void draw_play_scene(struct game_container *gc) {
    struct data *const pd = (struct data *)gc->scene.data;
}

void unload_play_scene(struct game_container *gc) {
    SDL_Log("Start unload play scene");

    free(gc->scene.data);

    SDL_Log("Unload play scene done");
}
