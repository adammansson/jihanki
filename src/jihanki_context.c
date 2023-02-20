#include "jihanki_context.h"
#include "jihanki_component.h"

context_t *context_new(SDL_Window *window, SDL_Renderer *renderer) {
  context_t *context;

  context = malloc(sizeof(context_t));
  context->window = window;
  context->renderer = renderer;
  context->components = NULL;
  context->component_count = 0;

  return context;
}

void context_add_component(context_t *context, component_t *component) {
  context->components = comnode_new(component, context->components);
  context->component_count++;
}

void context_draw(context_t *context) {
  comnode_t *node;

  node = context->components;
  while (node) {
    component_draw(node->component, context->renderer);
    node = node->next;
  }
}

void context_trigger_event(context_t *context, SDL_Event *event) {
  comnode_t *node;

  node = context->components;
  while (node) {
    component_trigger_event(node->component, event);
    node = node->next;
  }
}
