#ifndef __SHIP_H
#define __SHIP_H

#include "game.h"

#define SHIP_POINTS 8

typedef struct {
    SDL_FPoint *points;
    int start, end;
    bool engine_work;
} ship_t;

void draw_ship(state_t *state, ship_t *ship);
void dispose_ship(ship_t *ship);

#endif //__SHIP_H

