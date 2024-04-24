#ifndef GAME_SCENE_COMMON_H
#define GAME_SCENE_COMMON_H

#include "SDL.h"

struct game_container;

struct scene {
    void (*load)(struct game_container *gc);
    void (*update)(struct game_container *gc);
    void (*draw)(struct game_container *gc);
    void (*unload)(struct game_container *gc);
    void *data;
};

struct game_container {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int internal_width;
    int internal_height;
    struct scene scene;
};

void change_scene(struct game_container *gc, 
    void (*load)(struct game_container *gc), 
    void (*update)(struct game_container *gc), 
    void (*draw)(struct game_container *gc), 
    void (*unload)(struct game_container *gc)
);

void load_test_scene(struct game_container *gc);
void update_test_scene(struct game_container *gc);
void draw_test_scene(struct game_container *gc);
void unload_test_scene(struct game_container *gc);

#endif
