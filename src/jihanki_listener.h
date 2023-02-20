#ifndef JIHANKI_LISTENER_H
#define JIHANKI_LISTENER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct component component_t;

typedef struct listener {
  unsigned int type;
  void (*listener_function)(component_t *, SDL_Event *);
} listener_t;

typedef struct lisnode {
  listener_t *listener;
  struct lisnode *next;
} lisnode_t;

listener_t *listener_new(int type,
                         void (*listener_function)(component_t *, SDL_Event *));

lisnode_t *lisnode_new(listener_t *listener, lisnode_t *next);

#endif // JIHANKI_LISTENER_H
