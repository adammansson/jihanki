#include "jihanki_button.h"
#include "jihanki_component.h"

static void mousemotion_function(component_t *component, SDL_Event *event) {
  SDL_Point point;
  SDL_bool point_in_rect;

  point = (SDL_Point){event->button.x, event->button.y};
  point_in_rect = SDL_PointInRect(&point, &component->rect);

  if (point_in_rect && !(component->flags & (1 << HOVERED))) {
    component->flags |= (1 << HOVERED);
    component->color.r -= 50;
    component->color.g -= 50;
    component->color.b -= 50;
    component->flags |= (1 << HAS_CHANGED);
    printf("Entered button at: %d %d\n", component->rect.x, component->rect.y);
    return;
  }

  if (!point_in_rect && component->flags & (1 << HOVERED)) {
    component->flags &= ~(1 << HOVERED);
    component->color.r += 50;
    component->color.g += 50;
    component->color.b += 50;
    component->flags |= (1 << HAS_CHANGED);
    printf("Left button at: %d %d\n", component->rect.x, component->rect.y);
    return;
  }
}

component_t *button_new(context_t *context, SDL_Rect rect, char *text) {
  component_t *button;

  button = component_new(context, rect, text);
  component_add_listener(button,
                         listener_new(SDL_MOUSEMOTION, &mousemotion_function));
  return button;
}
