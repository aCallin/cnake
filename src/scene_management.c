#include "game_scene_common.h"

void change_scene(struct game_container *const gc, 
    void (*const load)(struct game_container *const gc), 
    void (*const update)(struct game_container *const gc), 
    void (*const draw)(struct game_container *const gc), 
    void (*const unload)(struct game_container *const gc)
) {
    gc->scene.unload(gc);
    gc->scene.load = load;
    gc->scene.update = update;
    gc->scene.draw = draw;
    gc->scene.unload = unload;
    gc->scene.load(gc);
}
