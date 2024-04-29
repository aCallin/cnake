#include "sdl_util.h"

void render_text(
    TTF_Font *const font, 
    const char *const text, 
    const SDL_Color color, 
    SDL_Renderer *const renderer, 
    SDL_Surface **const surface, 
    SDL_Texture **const texture, 
    int *const width, 
    int *const height
) {
    SDL_FreeSurface(*surface);
    *surface = TTF_RenderText_Blended(font, text, color);
    if (*surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "render_text(): TTF_RenderText_Blended() returned NULL");
        return;
    }

    SDL_DestroyTexture(*texture);
    *texture = SDL_CreateTextureFromSurface(renderer, *surface);
    if (*texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "render_text(): SDL_CreateTextureFromSurface() returned NULL");
        return;
    }

    TTF_SizeText(font, text, width, height);
}
