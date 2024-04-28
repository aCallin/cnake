#include "apple.h"

void apple_load(struct apple *const apple, resources const resources, SDL_Renderer *const renderer, const int tile_dimension) {
    resources_load_texture(resources, renderer, "apple.png", "apple");
    apple->texture = resources_get(resources, "apple");
    SDL_QueryTexture(apple->texture, NULL, NULL, &apple->texture_size.x, &apple->texture_size.y);
    apple->tile.x = tile_dimension - 4;
    apple->tile.y = tile_dimension / 2;
}

void apple_draw(const struct apple *const apple, SDL_Renderer *const renderer, const int tile_size) {
    const SDL_Rect rect = {apple->tile.x * tile_size, apple->tile.y * tile_size, apple->texture_size.x, apple->texture_size.y};
    SDL_RenderCopy(renderer, apple->texture, NULL, &rect);
}

void apple_unload(const struct apple *const apple, resources const resources) {
    resources_unload(resources, "apple");
}

SDL_Point apple_get_tile(const struct apple *const apple) {
    return apple->tile;
}

void apple_set_tile(struct apple *const apple, const SDL_Point tile) {
    apple->tile = tile;
}
