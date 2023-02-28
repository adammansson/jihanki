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

component_t *button_0;
component_t *button_1;
component_t *button_2;
component_t *button_3;
component_t *button_4;
component_t *button_5;
component_t *button_6;
component_t *button_7;
component_t *button_8;
component_t *button_9;
component_t *button_delete;
component_t *button_clear;
component_t *textfield;

static void addtotextfield_function(component_t *component, SDL_Event *event) {
  SDL_Point point;
  SDL_bool point_in_rect;
  char *text;

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

static void deletetextfield_function(component_t *component, SDL_Event *event) {
  SDL_Point point;
  SDL_bool point_in_rect;
  size_t text_length;

  point = (SDL_Point){event->button.x, event->button.y};
  point_in_rect = SDL_PointInRect(&point, &component->rect);

  if (event->button.button == SDL_BUTTON_LEFT && point_in_rect) {
    text_length = strlen(textfield->text);
    if (text_length > 0) {
      textfield->text[strlen(textfield->text) - 1] = '\0';
      component_set_text(textfield, textfield->text);
    }
    printf("Length of textfield: %lu\n", strlen(textfield->text));
    printf("Pressed button at: %d %d\n", component->rect.x, component->rect.y);
  }
}

static void cleartextfield_function(component_t *component, SDL_Event *event) {
  SDL_Point point;
  SDL_bool point_in_rect;

  point = (SDL_Point){event->button.x, event->button.y};
  point_in_rect = SDL_PointInRect(&point, &component->rect);

  if (event->button.button == SDL_BUTTON_LEFT && point_in_rect) {
    if (strlen(textfield->text) > 0) {
      component_set_text(textfield, "");
    }
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

  button_1 = button_new(
      context, (SDL_Rect){0, BUTTON_START, BUTTON_SIDE, BUTTON_SIDE}, "1");
  component_add_listener(
      button_1, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_2 = button_new(context,
                        (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET, BUTTON_START,
                                   BUTTON_SIDE, BUTTON_SIDE},
                        "2");
  component_add_listener(
      button_2, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_3 = button_new(context,
                        (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                                   BUTTON_START, BUTTON_SIDE, BUTTON_SIDE},
                        "3");
  component_add_listener(
      button_3, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_4 =
      button_new(context,
                 (SDL_Rect){0, BUTTON_START + BUTTON_OFFSET + BUTTON_SIDE,
                            BUTTON_SIDE, BUTTON_SIDE},
                 "4");
  component_add_listener(
      button_4, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_5 = button_new(context,
                        (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET,
                                   BUTTON_START + BUTTON_OFFSET + BUTTON_SIDE,
                                   BUTTON_SIDE, BUTTON_SIDE},
                        "5");
  component_add_listener(
      button_5, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_6 = button_new(context,
                        (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                                   BUTTON_START + BUTTON_OFFSET + BUTTON_SIDE,
                                   BUTTON_SIDE, BUTTON_SIDE},
                        "6");
  component_add_listener(
      button_6, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_7 =
      button_new(context,
                 (SDL_Rect){0, BUTTON_START + 2 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "7");
  component_add_listener(
      button_7, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_8 =
      button_new(context,
                 (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET,
                            BUTTON_START + 2 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "8");
  component_add_listener(
      button_8, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_9 =
      button_new(context,
                 (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                            BUTTON_START + 2 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "9");
  component_add_listener(
      button_9, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_delete =
      button_new(context,
                 (SDL_Rect){0, BUTTON_START + 3 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "D");

  component_add_listener(
      button_delete,
      listener_new(SDL_MOUSEBUTTONDOWN, &deletetextfield_function));

  button_0 =
      button_new(context,
                 (SDL_Rect){BUTTON_SIDE + BUTTON_OFFSET,
                            BUTTON_START + 3 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "0");
  component_add_listener(
      button_0, listener_new(SDL_MOUSEBUTTONDOWN, &addtotextfield_function));

  button_clear =
      button_new(context,
                 (SDL_Rect){2 * (BUTTON_SIDE + BUTTON_OFFSET),
                            BUTTON_START + 3 * (BUTTON_OFFSET + BUTTON_SIDE),
                            BUTTON_SIDE, BUTTON_SIDE},
                 "C");
  component_add_listener(button_clear, listener_new(SDL_MOUSEBUTTONDOWN,
                                                    &cleartextfield_function));

  textfield = component_new(context, (SDL_Rect){0, 100, WINDOW_WIDTH, 100}, "");
  textfield->flags &= ~(1 << TEXT_CENTERED);

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
