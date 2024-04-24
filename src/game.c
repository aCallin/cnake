#include "game.h"

#include <SDL.h>

#define WINDOW_TITLE "cnake"
#define WINDOW_POS SDL_WINDOWPOS_CENTERED
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 700

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
    SDL_Window *const window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_POS, WINDOW_POS, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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
            elapsed_time -= UPDATE_RATE;
        }

        // Draw
        if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0)
            LOG_ERROR
        if (SDL_RenderClear(renderer) < 0)
            LOG_ERROR
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}
