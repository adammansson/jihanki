#ifndef JIHANKI_COMPONENT_H
#define JIHANKI_COMPONENT_H

#include "jihanki_context.h"
#include "jihanki_listener.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum COMPONENT_FLAGS { TEXT_CHANGED = 0, TEXT_CENTERED, HOVERED };

typedef struct component {
  SDL_Rect rect;
  SDL_Color color;
  char *text;

  TTF_Font *font;
  SDL_Color font_color;
  SDL_Texture *font_texture;
  SDL_Rect font_rect;

  unsigned int flags;

  lisnode_t *listeners;
} component_t;

typedef struct comnode {
  component_t *component;
  struct comnode *next;
} comnode_t;

component_t *component_new(context_t *context, SDL_Rect rect, char *text);

comnode_t *comnode_new(component_t *component, comnode_t *next);

void component_draw(component_t *component, SDL_Renderer *renderer);

void component_add_listener(component_t *component, listener_t *listener);

void component_trigger_event(component_t *component, SDL_Event *event);

void component_set_text(component_t *component, char *text);

void component_free(component_t *component);

#endif // JIHANKI_COMPONENT_H
