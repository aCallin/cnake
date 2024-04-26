#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL.h"

/*
 * To do: shrink entries when small enough
*/

typedef struct resources *resources;
enum resource_type { resource_type_texture };

resources create_resources();
int load_resource(resources resources, SDL_Renderer *renderer, const char *resource_file_name, enum resource_type type, const char *tag);
void *get_resource(resources resources, const char *tag);
void unload_resource(resources resources, const char *tag);
void destroy_resources(resources resources);

#endif
