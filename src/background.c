#include "background.h"

#include "util/sdl_util.h"

void background_load(struct background *const background, resources const resources, SDL_Renderer *const renderer, const int internal_width) {
    resources_load_font(resources, "Komigo3D-Regular.ttf", "font", 36);
    background->font = resources_get(resources, "font");
    background->text_color.r = 255;
    background->text_color.g = 255;
    background->text_color.b = 255;
    background->text_color.a = SDL_ALPHA_OPAQUE;
    background->text_surface = NULL;
    background->text_texture = NULL;
    render_text(background->font, "Press D to start", background->text_color, renderer, &background->text_surface, 
        &background->text_texture, &background->text_rect.w, &background->text_rect.h);
    background->text_rect.x = (internal_width / 2) - (background->text_rect.w / 2);
    background->text_rect.y = internal_width;
}

void background_draw(struct background *const background, SDL_Renderer *const renderer, const int tile_size, const int tile_dimension) {
    // Tiles
    SDL_Rect tile = {0, 0, tile_size, tile_size};
    SDL_bool switch_color;
    for (int y = 0; y < tile_dimension; y++) {
        switch_color = y % 2;
        for (int x = 0; x < tile_dimension; x++) {
            tile.x = x * tile_size;
            tile.y = y * tile_size;
            (switch_color) ? SDL_SetRenderDrawColor(renderer, 170, 215, 81, SDL_ALPHA_OPAQUE) : SDL_SetRenderDrawColor(renderer, 162, 209, 73, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &tile);
            switch_color = !switch_color;
        }
    }

    // Text
    SDL_RenderCopy(renderer, background->text_texture, NULL, &background->text_rect);
}

void background_unload(struct background *const background, resources const resources) {
    SDL_DestroyTexture(background->text_texture);
    SDL_FreeSurface(background->text_surface);
    resources_unload(resources, "font");
}
