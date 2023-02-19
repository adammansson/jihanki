#ifndef JIHANKI_COMPONENT_H
#define JIHANKI_COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct component component_t;

typedef struct listener {
  unsigned int type;
  void (*listener_function)(component_t *, SDL_Event *);
} listener_t;

typedef struct lisnode {
  listener_t *listener;
  struct lisnode *next;
} lisnode_t;

listener_t *new_listener(int type,
                         void (*listener_function)(component_t *, SDL_Event *));

lisnode_t *new_lisnode(listener_t *listener, lisnode_t *next);

typedef struct component {
  SDL_Rect rect;
  SDL_Color color;

  int hovered;

  void (*draw_function)(struct component *, SDL_Renderer *);

  lisnode_t *listeners;
} component_t;

component_t *new_component(SDL_Rect rect, SDL_Color color,
                           void (*draw_function)(struct component *,
                                                 SDL_Renderer *));

void draw_component(component_t *component, SDL_Renderer *renderer);

void add_listener(component_t *component, listener_t *listener);

void trigger_event_component(component_t *component, SDL_Event *event);

void free_component(component_t *component);

#endif // JIHANKI_COMPONENT_H
