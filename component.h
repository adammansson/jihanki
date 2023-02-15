//
// Created by adam on 2/15/23.
//

#ifndef JIHANKI_COMPONENT_H
#define JIHANKI_COMPONENT_H

#include <SDL2/SDL.h>
#include "listener.h"

typedef struct component {
    int x, y;
    int width, height;

    struct {
        unsigned char hovered : 1;
        unsigned char toggled : 1;
        unsigned char pressed : 1;
    };

    struct listener_node *listeners;

    SDL_Rect rect;

    SDL_Color color;
} component_t;

typedef struct cnode {
    component_t *component;
    struct cnode *next;
} cnode_t;

component_t *new_component(int x, int y, int width, int height, int red, int green, int blue);

void draw_component(SDL_Renderer *renderer, component_t *component);

void add_listener(component_t *component, listener_t listener);

cnode_t *new_cnode(component_t *component, cnode_t *next);

void draw_components(SDL_Renderer *renderer, cnode_t *cnode);

void free_components(cnode_t *cnode);

#endif //JIHANKI_COMPONENT_H
