#ifndef __SHIP_H
#define __SHIP_H

#include "game.h"
#include <SDL2/SDL_rect.h>

#define SHIP_POINTS 9
#define ROTATION_ANGLE 15
#define BULLET_SPEED 4

typedef struct {
    SDL_FPoint position;
    // SDL_FPoint velocity;
    float angle;
    bool show;
} bullet_t;

typedef struct {
    SDL_FPoint *points;
    int start, end;
    bool engine_work;
    float angle;
    bullet_t *bullets;
} ship_t;

typedef enum {
    ROT_LEFT = -1,
    ROT_RIGHT = 1,
} rotation_t;

void draw_ship(state_t *state, ship_t *ship);
void draw_bullets(state_t *state, ship_t *ship);
void rotate_ship(ship_t *ship, rotation_t rot);
void update_bullet(float delta_time, bullet_t *bullet);
void dispose_ship(ship_t *ship);

#endif //__SHIP_H

