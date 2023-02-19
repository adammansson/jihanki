#include "component.h"

listener_t *new_listener(int type, void (*listener_function)(component_t *,
                                                             SDL_Event *)) {
  listener_t *listener;

  listener = malloc(sizeof(listener_t));
  listener->type = type;
  listener->listener_function = listener_function;

  return listener;
}
lisnode_t *new_lisnode(listener_t *listener, lisnode_t *next) {
  lisnode_t *lisnode;

  lisnode = malloc(sizeof(lisnode_t));
  lisnode->listener = listener;
  lisnode->next = next;

  return lisnode;
}

component_t *new_component(SDL_Rect rect, SDL_Color color,
                           void (*draw_function)(struct component *,
                                                 SDL_Renderer *)) {
  component_t *component;

  component = malloc(sizeof(component_t));

  component->rect = rect;
  component->color = color;

  component->hovered = 0;

  component->draw_function = draw_function;
  component->listeners = NULL;

  return component;
}

void draw_component(component_t *component, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, component->color.r, component->color.g,
                         component->color.b, 0);
  SDL_RenderFillRect(renderer, &component->rect);
}

void add_listener(component_t *component, listener_t *listener) {
  component->listeners = new_lisnode(listener, component->listeners);
}

void trigger_event_component(component_t *component, SDL_Event *event) {
  lisnode_t *current;

  current = component->listeners;
  while (current != NULL) {
    if (current->listener->type == event->type) {
      current->listener->listener_function(component, event);
    }
    current = current->next;
  }
}

void free_component(component_t *component) { free(component); }
