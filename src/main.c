#include "jihanki_component.h"
#include "jihanki_context.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_TITLE "jihanki"

void init_window(SDL_Window **window, SDL_Renderer **renderer, int width,
                 int height) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window,
                              renderer);

  if (!*window || !*renderer) {
    fprintf(stderr, "ERROR: %s", SDL_GetError());
    exit(1);
  }

  SDL_SetWindowTitle(*window, WINDOW_TITLE);
  SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
  SDL_RenderClear(*renderer);
  SDL_RenderPresent(*renderer);
}

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

  if (pointInRect && !component->hovered) {
    component->hovered = 1;
    component->color.r -= 50;
    component->color.g -= 50;
    component->color.b -= 50;
    printf("Entered button at: %d %d\n", component->rect.x, component->rect.y);
    return;
  }

  if (!pointInRect && component->hovered) {
    component->hovered = 0;
    component->color.r += 50;
    component->color.g += 50;
    component->color.b += 50;
    printf("Left button at: %d %d\n", component->rect.x, component->rect.y);
    return;
  }
}

int main(void) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  bool quit;
  context_t *context;
  component_t *button0;
  component_t *button1;
  component_t *button2;
  component_t *textfield0;

  init_window(&window, &renderer, 600, 800);

  context = context_new(window, renderer);

  button0 = component_new((SDL_Rect){0, 110, 100, 100}, "0", context);
  button1 = component_new((SDL_Rect){110, 110, 100, 100}, "1", context);
  button2 = component_new((SDL_Rect){220, 110, 100, 100}, "2", context);
  textfield0 = component_new((SDL_Rect){0, 0, 200, 100}, "Enter text", context);

  component_add_listener(
      button0, listener_new(SDL_MOUSEBUTTONDOWN, leftmousebuttondown_function));
  component_add_listener(
      button1, listener_new(SDL_MOUSEBUTTONDOWN, leftmousebuttondown_function));
  component_add_listener(
      button2, listener_new(SDL_MOUSEBUTTONDOWN, leftmousebuttondown_function));
  component_add_listener(button0,
                         listener_new(SDL_MOUSEMOTION, mousemotion_function));
  component_add_listener(button1,
                         listener_new(SDL_MOUSEMOTION, mousemotion_function));
  component_add_listener(button2,
                         listener_new(SDL_MOUSEMOTION, mousemotion_function));

  quit = false;
  while (!quit) {
    // component_draw(button0, renderer);
    // component_draw(button1, renderer);
    // component_draw(button2, renderer);
    // component_draw(textfield0, renderer);
    context_draw(context);

    while (SDL_PollEvent(&event)) {
      // component_trigger_event(button0, &event);
      // component_trigger_event(button1, &event);
      // component_trigger_event(button2, &event);
      // component_trigger_event(textfield0, &event);
      context_trigger_event(context, &event);

      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
  }

  component_free(button0);
  component_free(button1);
  component_free(button2);
  component_free(textfield0);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
