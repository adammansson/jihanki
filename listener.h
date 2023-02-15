//
// Created by adam on 2/15/23.
//

#ifndef JIHANKI_LISTENER_H
#define JIHANKI_LISTENER_H

typedef struct listener {
    int type;
} listener_t;

typedef struct lnode {
    listener_t *listener;
    struct lnode *next;
} lnode_t;

#endif //JIHANKI_LISTENER_H
