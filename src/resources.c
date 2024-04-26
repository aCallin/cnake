#include "resources.h"

#include "SDL_image.h"
#include <string.h>

#define RESOURCES_FOLDER_NAME "res/"

#define INITIAL_CAPACITY 5
#define GROWTH_FACTOR 1.5

struct resource_entry {
    enum resource_type type;
    char *tag;
    void *data;
};

struct resources {
    char *resources_path;
    int resources_path_length;

    struct resource_entry *resource_entries;
    int resource_entries_capacity;
    int resource_entries_size;
};

/**
 * Free the pointer when you're done
*/ 
static char *resource_path(resources const resources, const char *const resource_file_name) {
    char *const resource_path = malloc((resources->resources_path_length + strlen(resource_file_name) + 1) * sizeof(char));
    if (resource_path == NULL)
        return NULL;
    strcpy(resource_path, resources->resources_path);
    strcat(resource_path, resource_file_name);
    return resource_path;
}

resources create_resources() {
    resources resources = malloc(sizeof(struct resources));
    if (resources == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "create_resource(): resources malloc returned NULL");
        return NULL;
    }
    
    // Get path to exe
    char *const exe_path = SDL_GetBasePath();
    if (exe_path == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "create_resource(): exe_path NULL");
        free(resources);
        return NULL;
    }
    const int exe_path_length = strlen(exe_path);

    // Get path to resources
    const int resources_folder_name_length = strlen(RESOURCES_FOLDER_NAME);
    resources->resources_path_length = exe_path_length + resources_folder_name_length;
    resources->resources_path = malloc((exe_path_length + resources_folder_name_length + 1) * sizeof(char));
    if (resources->resources_path == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "create_resource(): resources_path malloc returned NULL");
        SDL_free(exe_path);
        free(resources);
        return NULL;
    }
    strcpy(resources->resources_path, exe_path);
    strcat(resources->resources_path, RESOURCES_FOLDER_NAME);

    // Resource entries
    resources->resource_entries = malloc(INITIAL_CAPACITY * sizeof(struct resource_entry));
    resources->resource_entries_capacity = INITIAL_CAPACITY;
    resources->resource_entries_size = 0;

    // Clean up
    SDL_free(exe_path);

    return resources;
}

int load_resource(resources const resources, SDL_Renderer *const renderer, const char *const resource_file_name, enum resource_type type, const char *const tag) {
    // Increase capacity if needed
    if (resources->resource_entries_size == resources->resource_entries_capacity) {
        const int new_capacity = resources->resource_entries_capacity * GROWTH_FACTOR;
        struct resource_entry *const new_entries = malloc(sizeof(struct resource_entry) * new_capacity);
        if (new_entries == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "load_resource(): new_entries malloc returned NULL");
            return 0;
        }
        memcpy(new_entries, resources->resource_entries, sizeof(struct resource_entry) * resources->resource_entries_capacity);
        free(resources->resource_entries);
        resources->resource_entries = new_entries;
        resources->resource_entries_capacity = new_capacity;
    }

    // Populate entry...
    struct resource_entry *const entry = &resources->resource_entries[resources->resource_entries_size];

    // ... type
    entry->type = type;

    // ... tag
    entry->tag = malloc((strlen(tag) + 1) * sizeof(char));
    if (entry->tag == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "load_resource(): entry->tag malloc returned NULL");
        return 0;
    }
    strcpy(entry->tag, tag);

    // ... data
    char *const load_path = resource_path(resources, resource_file_name);
    if (load_path == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "load_resource(): resource_path() returned NULL");
        free(entry->tag);
        return 0;
    }
    SDL_bool invalid_type = SDL_FALSE;
    switch (type) {
        case resource_type_texture:
            entry->data = IMG_LoadTexture(renderer, load_path);
            break;
        default:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "resources_load(): unrecognized resource type");
            invalid_type = SDL_TRUE;
            break;
    }
    if (invalid_type) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "load_resource(): invalid type");
        free(entry->tag);
        free(load_path);
        return 0;
    }

    // Increase size if all went well
    resources->resource_entries_size++;

    // Clean up
    free(load_path);
}

void *get_resource(resources const resources, const char *const tag) {
    for (int i = 0; i < resources->resource_entries_size; i++) {
        struct resource_entry *const entry = &resources->resource_entries[i];
        if (strcmp(tag, entry->tag) == 0)
            return entry->data;
    }
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "resources_get(): resource not found");
    return NULL;
}

void unload_resource(resources const resources, const char *const tag) {
    // Locate resource
    for (int i = 0; i < resources->resource_entries_size; i++) {
        struct resource_entry *const entry = &resources->resource_entries[i];
        if (strcmp(tag, entry->tag) == 0) {
            // Free allocated memory in entry
            free(entry->tag);
            switch (entry->type) {
                case resource_type_texture:
                    SDL_DestroyTexture(entry->data);
                    break;
            }

            // Shift entries down
            void *const destination = resources->resource_entries + i;
            const void *const source = resources->resource_entries + i + 1;
            const int num_entries = (resources->resource_entries_size - i) - 1;
            const int num_bytes = sizeof(struct resource_entry) * num_entries;
            memmove(destination, source, num_bytes);
            resources->resource_entries_size--;
            return;
        }
    }
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "unload_resource(): resource not found");
}

void destroy_resources(resources const resources) {
    // Warn + unload remaining resources
    if (resources->resource_entries_size > 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "destroy_resources(): not all resources have been unloaded");
        for (int i = resources->resource_entries_size - 1; i >= 0; i--) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "resource tag: %s", resources->resource_entries[i].tag);
            unload_resource(resources, resources->resource_entries[i].tag);
        }
    }

    // Further clean up
    free(resources->resource_entries);
    free(resources->resources_path);
    free(resources);
}
