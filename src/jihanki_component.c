#include "jihanki_component.h"
#include "jihanki_context.h"
#include <string.h>

static SDL_Rect calculate_font_rect(SDL_Rect rect, SDL_Surface *surface,
                                    int centered_text) {
  int font_rectw, font_recth;
  int font_rectx, font_recty;

  if (surface == NULL) {
    return (SDL_Rect){0, 0, 0, 0};
  }

  font_rectw = surface->w;
  font_recth = surface->h;
  font_recty = rect.y + (rect.h - font_recth) / 2;
  if (centered_text) {
    font_rectx = rect.x + (rect.w - font_rectw) / 2;
    return (SDL_Rect){font_rectx, font_recty, font_rectw, font_recth};
  }

  font_rectx = rect.w - font_rectw;
  return (SDL_Rect){font_rectx, font_recty, font_rectw, font_recth};
}

component_t *component_new(context_t *context, SDL_Rect rect, char *text) {
  component_t *component;
  int font_pts;

  component = malloc(sizeof(component_t));

  component->rect = rect;
  component->color = (SDL_Color){255, 255, 255, 255};
  component->text = malloc((strlen(text) + 1) * sizeof(char));
  strcpy(component->text, text);

  font_pts = (int)(rect.h * 0.75);
  component->font = TTF_OpenFont(
      "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf", font_pts);
  component->font_color = (SDL_Color){0, 0, 0, 255};

  component->flags = 0;

  // set TEXT_CHANGED to 1 to create everything
  // regarding fonts on first call to component_draw
  component->flags |= (1 << TEXT_CHANGED);

  // set CENTERED_TEXT as standard
  component->flags |= (1 << TEXT_CENTERED);

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
  SDL_Surface *surface;

  SDL_SetRenderDrawColor(renderer, component->color.r, component->color.g,
                         component->color.b, 0);
  SDL_RenderFillRect(renderer, &component->rect);

  if (component->flags & (1 << TEXT_CHANGED)) {
    // remake font_texture if text has changed
    surface = TTF_RenderText_Solid(component->font, component->text,
                                   component->font_color);
    component->font_rect = calculate_font_rect(
        component->rect, surface, component->flags & (1 << TEXT_CENTERED));
    component->font_texture = SDL_CreateTextureFromSurface(renderer, surface);
    component->flags &= ~(1 << TEXT_CHANGED);
  }
  SDL_RenderCopy(renderer, component->font_texture, NULL,
                 &component->font_rect);
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

void component_set_text(component_t *component, char *text) {
  component->text = realloc(component->text, strlen(text) + 1);
  strcpy(component->text, text);
  component->flags |= (1 << TEXT_CHANGED);
}

void component_free(component_t *component) {
  free(component->text);
  free(component);
}
