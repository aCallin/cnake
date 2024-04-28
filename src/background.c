#include "background.h"

static SDL_Point set_text(struct background *const background, SDL_Renderer *const renderer, const char *const text) {
    SDL_Point text_size = {0, 0};

    background->text_surface = TTF_RenderText_Blended(background->font, text, background->text_color);
    if (background->text_surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "set_text(): text_surface is NULL");
        return text_size;
    }
    background->text_texture = SDL_CreateTextureFromSurface(renderer, background->text_surface);
    if (background->text_texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "set_text(): text_texture is NULL");
        return text_size;
    }
    
    TTF_SizeText(background->font, text, &text_size.x, &text_size.y);
    return text_size;
}

void background_load(struct background *const background, resources const resources, SDL_Renderer *const renderer, const int internal_width) {
    resources_load_font(resources, "Komigo3D-Regular.ttf", "font", 36);
    background->font = resources_get(resources, "font");
    background->text_color.r = 255;
    background->text_color.g = 255;
    background->text_color.b = 255;
    background->text_color.a = SDL_ALPHA_OPAQUE;
    SDL_Point text_size = set_text(background, renderer, "Press D to start");
    background->text_rect.w = text_size.x;
    background->text_rect.h = text_size.y;
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
    resources_unload(resources, "font");
}
