#include "jihanki_listener.h"

listener_t *listener_new(int type, void (*listener_function)(component_t *,
                                                             SDL_Event *)) {
  listener_t *listener;

  listener = malloc(sizeof(listener_t));
  listener->type = type;
  listener->listener_function = listener_function;

  return listener;
}

lisnode_t *lisnode_new(listener_t *listener, lisnode_t *next) {
  lisnode_t *lisnode;

  lisnode = malloc(sizeof(lisnode_t));
  lisnode->listener = listener;
  lisnode->next = next;

  return lisnode;
}
