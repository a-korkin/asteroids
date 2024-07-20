#ifndef __SHIP_H
#define __SHIP_H

#include "game.h"

#define SHIP_POINTS 9

typedef struct {
    SDL_FPoint *points;
    int start, end;
    bool engine_work;
} ship_t;

typedef enum {
    ROT_LEFT = -1,
    ROT_RIGHT = 1,
} rotation_t;

void draw_ship(state_t *state, ship_t *ship);
void rotate_ship(ship_t *ship, rotation_t rot);
void dispose_ship(ship_t *ship);

#endif //__SHIP_H

