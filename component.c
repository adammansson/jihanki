//
// Created by adam on 2/15/23.
//

#include "component.h"

component_t *new_component(int x, int y, int width, int height, int red, int green, int blue) {
    component_t *component;

    component = malloc(sizeof(component_t));
    component->x = x;
    component->y = y;
    component->width = width;
    component->height = height;

    component->rect.x = x;
    component->rect.y = y;
    component->rect.w= width;
    component->rect.h = height;

    component->color.r= red;
    component->color.g = green;
    component->color.b = blue;

    return component;
}

void draw_component(SDL_Renderer *renderer, component_t *component) {
    SDL_SetRenderDrawColor(renderer, component->color.r, component->color.g, component->color.b, 0);
    SDL_RenderFillRect(renderer, &component->rect);
}

cnode_t *new_cnode(component_t *component, cnode_t *next) {
    cnode_t *cnode;

    cnode = malloc(sizeof(cnode_t));
    cnode->component = component;
    cnode->next = next;

    return cnode;
}

void draw_components(SDL_Renderer *renderer, cnode_t *cnode) {
    while (cnode != NULL) {
        draw_component(renderer, cnode->component);
        cnode = cnode->next;
    }
}

void free_components(cnode_t *cnode) {
    cnode_t *temp_node;

    while (cnode != NULL) {
        temp_node = cnode->next;
        free(cnode->component);
        free(cnode);
        cnode = temp_node;
    }
}
