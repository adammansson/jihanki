#include "jihanki_button.h"
#include "jihanki_component.h"
#include "jihanki_context.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_TITLE "jihanki"
#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (800)
#define BUTTON_SIDE (100)
#define BUTTON_START (300)
#define BUTTON_OFFSET (10)
#define TEXTFIELD_HEIGHT (100)

component_t *button0;
component_t *button1;
component_t *button2;
component_t *button3;
component_t *button4;
component_t *button5;
component_t *button6;
component_t *button7;
component_t *button8;
component_t *button9;
component_t *buttonDelete;
component_t *buttonClear;
component_t *textfield;

static void leftmousebuttondown_function(component_t *component,
                                         SDL_Event *event) {
  char *text;
  SDL_Point point;
  SDL_bool point_in_rect;

  point = (SDL_Point){event->button.x, event->button.y};
  point_in_rect = SDL_PointInRect(&point, &component->rect);

  if (event->button.button == SDL_BUTTON_LEFT && point_in_rect) {
    text = malloc(strlen(textfield->text) + strlen(component->text) + 1);
    strcpy(text, textfield->text);
    strcat(text, component->text);
    component_set_text(textfield, text);
    printf("Length of textfield: %lu\n", strlen(textfield->text));
    printf("Pressed button at: %d %d\n", component->rect.x, component->rect.y);
  }
}

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

  jihanki_init(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

  context = context_new(window, renderer);

  button1 = button_new(
      context, (SDL_Rect){0, BUTTON_START, BUTTON_SIDE, BUTTON_SIDE}, "1");
  component_add_listener(button1, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button2 = button_new(context,
                       (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET, BUTTON_START,
                                  BUTTON_SIDE, BUTTON_SIDE},
                       "2");
  component_add_listener(button2, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button3 = button_new(context,
                       (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                                  BUTTON_START, BUTTON_SIDE, BUTTON_SIDE},
                       "3");
  component_add_listener(button3, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button4 = button_new(context,
                       (SDL_Rect){0, BUTTON_START + BUTTON_OFFSET + BUTTON_SIDE,
                                  BUTTON_SIDE, BUTTON_SIDE},
                       "4");
  component_add_listener(button4, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button5 = button_new(context,
                       (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET,
                                  BUTTON_START + BUTTON_OFFSET + BUTTON_SIDE,
                                  BUTTON_SIDE, BUTTON_SIDE},
                       "5");
  component_add_listener(button5, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button6 = button_new(context,
                       (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                                  BUTTON_START + BUTTON_OFFSET + BUTTON_SIDE,
                                  BUTTON_SIDE, BUTTON_SIDE},
                       "6");
  component_add_listener(button6, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button7 =
      button_new(context,
                 (SDL_Rect){0, BUTTON_START + 2 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "7");
  component_add_listener(button7, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button8 =
      button_new(context,
                 (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET,
                            BUTTON_START + 2 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "8");
  component_add_listener(button8, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  button9 =
      button_new(context,
                 (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                            BUTTON_START + 2 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "9");
  component_add_listener(button9, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  buttonDelete =
      button_new(context,
                 (SDL_Rect){0, BUTTON_START + 3 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "*");
  button0 =
      button_new(context,
                 (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET,
                            BUTTON_START + 3 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "0");
  component_add_listener(button0, listener_new(SDL_MOUSEBUTTONDOWN,
                                               &leftmousebuttondown_function));

  buttonClear =
      button_new(context,
                 (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                            BUTTON_START + 3 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "#");
  textfield = component_new(context, (SDL_Rect){0, 100, WINDOW_WIDTH, 100}, "");

  quit = false;
  while (!quit) {
    context_draw(context);

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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
  }

  context_free(context);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  printf("Exiting...\n");
}
