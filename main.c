#include "component.h"
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
  int a = TTF_Init();
  printf("%d\n", a);

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
  component_t *button0;
  component_t *button1;
  component_t *textfield0;

  init_window(&window, &renderer, 600, 800);

  button0 = new_component((SDL_Rect){0, 110, 100, 100},
                          (SDL_Color){255, 255, 255, 255}, draw_component);
  button1 = new_component((SDL_Rect){110, 110, 100, 100},
                          (SDL_Color){255, 255, 255, 255}, draw_component);
  textfield0 = new_component((SDL_Rect){0, 0, 300, 100},
                             (SDL_Color){255, 255, 255, 255}, draw_component);

  add_listener(button0,
               new_listener(SDL_MOUSEBUTTONDOWN, leftmousebuttondown_function));
  add_listener(button1,
               new_listener(SDL_MOUSEBUTTONDOWN, leftmousebuttondown_function));
  add_listener(button0, new_listener(SDL_MOUSEMOTION, mousemotion_function));
  add_listener(button1, new_listener(SDL_MOUSEMOTION, mousemotion_function));

  TTF_Font *font =
      TTF_OpenFont("/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf", 256);
  SDL_Color font_color = (SDL_Color){0, 0, 0, 255};
  SDL_Surface *surface = TTF_RenderText_Solid(font, "0", font_color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  quit = false;
  while (!quit) {
    button0->draw_function(button0, renderer);
    SDL_RenderCopy(renderer, texture, NULL, &button0->rect);
    button1->draw_function(button1, renderer);
    textfield0->draw_function(textfield0, renderer);

    while (SDL_PollEvent(&event)) {
      trigger_event_component(button0, &event);
      trigger_event_component(button1, &event);
      trigger_event_component(textfield0, &event);

      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }

    SDL_RenderPresent(renderer);

    /*
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    */
  }

  free_component(button0);
  free_component(button1);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
