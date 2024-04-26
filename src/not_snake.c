#include "not_snake.h"

static void draw_tiles(SDL_Renderer *const renderer, const int tile_size, const int tile_dimension) {
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

static void draw_apple(SDL_Renderer *const renderer, SDL_Texture *const apple_texture, const SDL_Rect *const apple_rect) {
    SDL_RenderCopy(renderer, apple_texture, NULL, apple_rect);
}

void load_not_snake(struct not_snake *const ns, resources const resources, SDL_Renderer *const renderer, const int tile_size, const int tile_dimension) {
    load_resource(resources, renderer, "apple.png", resource_type_texture, "apple");
    ns->apple_texture = get_resource(resources, "apple");
    ns->apple_rect.x = (tile_dimension - 4) * tile_size;
    ns->apple_rect.y = (tile_dimension / 2) * tile_size;
    SDL_QueryTexture(ns->apple_texture, NULL, NULL, &ns->apple_rect.w, &ns->apple_rect.h);
}

void draw_not_snake(struct not_snake *const ns, SDL_Renderer *const renderer, const int tile_size, const int tile_dimension) {
    draw_tiles(renderer, tile_size, tile_dimension);
    draw_apple(renderer, ns->apple_texture, &ns->apple_rect);
}

void unload_not_snake(struct not_snake *const ns, resources const resources) {
    unload_resource(resources, "apple");
}
