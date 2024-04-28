#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL.h"

typedef struct resources *resources;

resources resources_create();
void resources_load_texture(resources resources, SDL_Renderer *renderer, const char *file_name, const char *tag);
void resources_load_font(resources resources, const char *file_name, const char *tag, int point_size);
void *resources_get(resources resources, const char *tag);
void resources_unload(resources resources, const char *tag);
void resources_destroy(resources resources);

#endif
