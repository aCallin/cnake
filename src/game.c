#include "game.h"

#include "SDL.h"
#include "game_scene_common.h"

#define WINDOW_TITLE "cnake"
#define WINDOW_POS SDL_WINDOWPOS_CENTERED
#define INTERNAL_WIDTH 600
#define INTERNAL_HEIGHT 700

#define UPDATES_PER_SECOND 60
#define UPDATE_RATE (1000.0f / UPDATES_PER_SECOND)

#define LOG_ERROR SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "run_game(): %s", SDL_GetError());

int run_game() {
    // Initialize video
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        LOG_ERROR
        return 1;
    }

    // Create window and renderer
    SDL_Window *const window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_POS, WINDOW_POS, INTERNAL_WIDTH, INTERNAL_HEIGHT, 0);
    if (window == NULL) {
        LOG_ERROR
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return 1;
    }
    SDL_Renderer *const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        LOG_ERROR
        SDL_DestroyWindow(window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return 1;
    }

    // Initialize game container and load in the first scene
    struct game_container game_container;
    game_container.window = window;
    game_container.renderer = renderer;
    game_container.internal_width = INTERNAL_WIDTH;
    game_container.internal_height = INTERNAL_HEIGHT;
    // game_container.scene.load = load_test_scene;
    // game_container.scene.update = update_test_scene;
    // game_container.scene.draw = draw_test_scene;
    // game_container.scene.unload = unload_test_scene;
    game_container.scene.load = load_play_scene;
    game_container.scene.update = update_play_scene;
    game_container.scene.draw = draw_play_scene;
    game_container.scene.unload = unload_play_scene;
    game_container.scene.load(&game_container);

    // Do the game loop
    SDL_bool running = SDL_TRUE;
    Uint64 previous_time = SDL_GetTicks64();
    float elapsed_time = 0;
    while (running) {
        // Poll events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
                break;
            }
        }
        if (running == SDL_FALSE)
            break;

        // Update
        const Uint64 current_time = SDL_GetTicks64();
        elapsed_time += current_time - previous_time;
        previous_time = current_time;
        while (elapsed_time >= UPDATE_RATE) {
            game_container.scene.update(&game_container);
            elapsed_time -= UPDATE_RATE;
        }

        // Draw
        if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0)
            LOG_ERROR
        if (SDL_RenderClear(renderer) < 0)
            LOG_ERROR
        game_container.scene.draw(&game_container);
        SDL_RenderPresent(renderer);
    }

    // Clean up
    game_container.scene.unload(&game_container);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}
