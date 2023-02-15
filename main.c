//
// Created by adam on 2/15/23.
//
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "component.h"

#define WINDOW_TITLE "jihanki"

void init_window(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer);

    if (!*window || !*renderer) {
        fprintf(stderr, "ERROR: %s", SDL_GetError());
        exit(1);
    }

    SDL_SetWindowTitle(*window, WINDOW_TITLE);
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
}

int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool quit;
    component_t *button0;
    component_t *button1;
    cnode_t *components;

    init_window(&window, &renderer, 600, 800);

    button0 = new_component(0, 0, 200, 100, 255, 255, 255);
    button1 = new_component(0, 110, 200, 100, 255, 0, 0);

    components = new_cnode(button0, components);
    components = new_cnode(button1, components);

    quit = false;
    while (!quit) {
        draw_components(renderer, components);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
            }
        }

        SDL_RenderPresent(renderer);
    }

    free_components(components);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}