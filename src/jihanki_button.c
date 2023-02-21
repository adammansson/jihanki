#include "jihanki_button.h"
#include "jihanki_component.h"

static void leftmousebuttondown_function(component_t *component,
                                         SDL_Event *event) {
  SDL_Point point = {event->button.x, event->button.y};
  SDL_bool pointInRect = SDL_PointInRect(&point, &component->rect);

  if (pointInRect && event->button.button == SDL_BUTTON_LEFT) {
    printf("Pressed button at: %d %d\n", component->rect.x, component->rect.y);
  }
}

static void mousemotion_function(component_t *component, SDL_Event *event) {
  SDL_Point point = {event->button.x, event->button.y};
  SDL_bool pointInRect = SDL_PointInRect(&point, &component->rect);

  if (pointInRect && !(component->flags & (1 << HOVERED))) {
    component->flags |= (1 << HOVERED);
    component->flags |= (1 << HAS_CHANGED);
    component->color.r -= 50;
    component->color.g -= 50;
    component->color.b -= 50;
    printf("Entered button at: %d %d\n", component->rect.x, component->rect.y);
    return;
  }

  if (!pointInRect && (component->flags & (1 << HOVERED))) {
    component->flags &= ~(1 << HOVERED);
    component->flags |= (1 << HAS_CHANGED);
    component->color.r += 50;
    component->color.g += 50;
    component->color.b += 50;
    printf("Left button at: %d %d\n", component->rect.x, component->rect.y);
    return;
  }
}

component_t *button_new(context_t *context, SDL_Rect rect, char *text) {
  component_t *button;

  button = component_new(context, rect, text);

  component_add_listener(
      button, listener_new(SDL_MOUSEBUTTONDOWN, &leftmousebuttondown_function));
  component_add_listener(button,
                         listener_new(SDL_MOUSEMOTION, &mousemotion_function));
  return button;
}
