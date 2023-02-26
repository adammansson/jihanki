#ifndef JIHANKI_CONTEXT_H
#define JIHANKI_CONTEXT_H

#include <SDL2/SDL.h>

typedef struct component component_t;
typedef struct comnode comnode_t;

typedef struct context {
  SDL_Window *window;
  SDL_Renderer *renderer;

  comnode_t *components;
  int component_count;
} context_t;

context_t *context_new(SDL_Window *window, SDL_Renderer *renderer);

void context_add_component(context_t *context, component_t *component);

void context_draw(context_t *context);

void context_trigger_event(context_t *context, SDL_Event *event);

void context_free(context_t *context);

#endif // JIHANKI_CONTEXT_H
