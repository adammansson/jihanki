#include "component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_TITLE "jihanki"

void init_window(SDL_Window **window, SDL_Renderer **renderer, int width,
                 int height) {
  SDL_Init(SDL_INIT_VIDEO);

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

int main(void) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  bool quit;
  component_t *button0;
  component_t *button1;
  component_t *button2;

  init_window(&window, &renderer, 600, 800);

  button0 = new_component((SDL_Rect){0, 0, 200, 100},
                          (SDL_Color){255, 255, 255, 255}, draw_component);
  button1 = new_component((SDL_Rect){0, 110, 200, 100},
                          (SDL_Color){255, 255, 255, 255}, draw_component);
  button2 = new_component((SDL_Rect){210, 110, 200, 100},
                          (SDL_Color){255, 255, 255, 255}, draw_component);

  quit = false;
  while (!quit) {
    button0->draw_function(renderer, button0);
    button1->draw_function(renderer, button1);
    button2->draw_function(renderer, button2);

    while (SDL_PollEvent(&event)) {
      trigger_event_component(button0, &event);
      trigger_event_component(button1, &event);
      trigger_event_component(button2, &event);

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
