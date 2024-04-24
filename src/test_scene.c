#include "game_scene_common.h"

struct data {
    SDL_Rect box;
    int move_speed;
    int move_direction_x, move_direction_y;
    const Uint8 *keyboard_state;
};

void load_test_scene(struct game_container *const gc) {
    SDL_Log("Start load test scene");

    gc->scene.data = malloc(sizeof(struct data));
    struct data *const td = (struct data *)gc->scene.data;

    td->box.x = 0;
    td->box.y = 0;
    td->box.w = 50;
    td->box.h = 50;
    td->move_speed = 3;
    td->move_direction_x = 1;
    td->move_direction_y = 1;

    td->keyboard_state = SDL_GetKeyboardState(NULL);

    SDL_Log("Load test scene done");
}

void update_test_scene(struct game_container *const gc) {
    struct data *const td = (struct data *)gc->scene.data;

    td->box.x += td->move_speed * td->move_direction_x;
    if (td->box.x <= 0 || (td->box.x + td->box.w) >= gc->internal_width) {
        td->box.x = (td->box.x <= 0) ? 0 : (gc->internal_width - 1) - td->box.w;
        td->move_direction_x = -td->move_direction_x;
    }
    td->box.y += td->move_speed * td->move_direction_y;
    if (td->box.y <= 0 || (td->box.y + td->box.h) >= gc->internal_height) {
        td->box.y = (td->box.y <= 0) ? 0 : (gc->internal_height - 1) - td->box.h;
        td->move_direction_y = -td->move_direction_y;
    }

    if (td->keyboard_state[SDL_SCANCODE_RETURN]) {
        SDL_Log("Changing scene...");
        change_scene(gc, load_test_scene, update_test_scene, draw_test_scene, unload_test_scene);
    }
}

void draw_test_scene(struct game_container *const gc) {
    struct data *const td = (struct data *)gc->scene.data;

    SDL_SetRenderDrawColor(gc->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gc->renderer, &td->box);
}

void unload_test_scene(struct game_container *const gc) {
    SDL_Log("Start unload test scene");

    free(gc->scene.data);

    SDL_Log("Unload test scene done");
}
