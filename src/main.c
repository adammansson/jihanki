#include "jihanki_button.h"
#include "jihanki_component.h"
#include "jihanki_context.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_TITLE "jihanki"

component_t *button0;
component_t *button1;
component_t *button2;
component_t *textfield0;

void jihanki_init(SDL_Window **window, SDL_Renderer **renderer, int width,
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

int main(void) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  bool quit;
  context_t *context;
  unsigned char counter;

  jihanki_init(&window, &renderer, 600, 800);

  context = context_new(window, renderer);

  button0 = button_new(context, (SDL_Rect){0, 110, 100, 100}, "0");
  button1 = button_new(context, (SDL_Rect){110, 110, 100, 100}, "1");
  button2 = button_new(context, (SDL_Rect){220, 110, 100, 100}, "2");
  textfield0 = component_new(context, (SDL_Rect){0, 0, 200, 100}, "Enter text");

  counter = 0;
  quit = false;
  while (!quit) {
    // forced redraw of all components if counter overflows
    context_draw(context, counter == 0);

    while (SDL_PollEvent(&event)) {
      context_trigger_event(context, &event);

      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);
    counter++;
  }

  context_free(context);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
