#ifndef JIHANKI_BUTTON_H
#define JIHANKI_BUTTON_H

#include "jihanki_context.h"
#include <SDL2/SDL.h>

component_t *button_new(context_t *context, SDL_Rect rect, char *text);

#endif // JIHANKI_BUTTON_H
