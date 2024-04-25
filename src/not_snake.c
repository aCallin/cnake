#include "not_snake.h"

void draw_tiles(SDL_Renderer *const renderer, const int tile_size, const int tile_dimension) {
    SDL_Rect tile = {0, 0, tile_size, tile_size};
    SDL_bool switch_color;
    for (int y = 0; y < tile_dimension; y++) {
        switch_color = y % 2;
        for (int x = 0; x < tile_dimension; x++) {
            tile.x = x * tile_size;
            tile.y = y * tile_size;
            (switch_color) ? SDL_SetRenderDrawColor(renderer, 170, 215, 81, SDL_ALPHA_OPAQUE) : 
                SDL_SetRenderDrawColor(renderer, 162, 209, 73, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &tile);
            switch_color = !switch_color;
        }
    }
}
