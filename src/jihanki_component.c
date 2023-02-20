#include "jihanki_component.h"
#include "jihanki_context.h"
#include <string.h>

component_t *component_new(SDL_Rect rect, char *text, context_t *context) {
  component_t *component;

  component = malloc(sizeof(component_t));

  component->rect = rect;
  component->color = (SDL_Color){255, 255, 255, 255};
  component->text = malloc((strlen(text) + 1) * sizeof(char));
  strcpy(component->text, text);

  component->font =
      TTF_OpenFont("/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf", 512);
  component->font_color = (SDL_Color){0, 0, 0, 255};
  SDL_Surface *surface = TTF_RenderText_Solid(component->font, component->text,
                                              component->font_color);
  component->font_texture =
      SDL_CreateTextureFromSurface(context->renderer, surface);

  component->hovered = 0;

  component->listeners = NULL;

  context_add_component(context, component);
  return component;
}

comnode_t *comnode_new(component_t *component, comnode_t *next) {
  comnode_t *comnode;

  comnode = malloc(sizeof(comnode_t));
  comnode->component = component;
  comnode->next = next;

  return comnode;
}

void component_draw(component_t *component, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, component->color.r, component->color.g,
                         component->color.b, 0);
  SDL_RenderFillRect(renderer, &component->rect);

  SDL_RenderCopy(renderer, component->font_texture, NULL, &component->rect);
}

void component_add_listener(component_t *component, listener_t *listener) {
  component->listeners = lisnode_new(listener, component->listeners);
}

void component_trigger_event(component_t *component, SDL_Event *event) {
  lisnode_t *current;

  current = component->listeners;
  while (current != NULL) {
    if (current->listener->type == event->type) {
      current->listener->listener_function(component, event);
    }
    current = current->next;
  }
}

void component_free(component_t *component) {
  free(component->text);
  free(component);
}
