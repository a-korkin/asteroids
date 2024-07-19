#ifndef __SHIP_H
#define __SHIP_H

#include "game.h"

typedef struct {
    SDL_FPoint *points;
} ship_t;

void draw_ship(state_t *state, ship_t *ship);
void dispose_ship(ship_t *ship);

#endif //__SHIP_H

