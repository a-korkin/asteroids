#ifndef __SHIP_H
#define __SHIP_H

#include "game.h"
#include <SDL2/SDL_rect.h>

#define SHIP_POINTS 9
#define ROTATION_ANGLE 15
#define BULLET_SPEED 4
#define SHIP_SPEED 3

typedef struct bullet {
    SDL_FPoint position;
    float angle;
    bool show;
    struct bullet *prev;
    struct bullet *next;
} bullet_t;

typedef struct {
    SDL_FPoint *points;
    int start, end;
    bool engine_work;
    float angle;
    bullet_t *bullets;
    bullet_t *last_bullet;
} ship_t;

typedef enum {
    ROT_LEFT = -1,
    ROT_RIGHT = 1,
} rotation_t;

void draw_ship(state_t *state, ship_t *ship);
void draw_bullets(state_t *state, ship_t *ship);
void rotate_ship(ship_t *ship, rotation_t rot);
void update_bullets(float delta_time, bullet_t *bullets);
void move_ship(float delta_time, ship_t *ship);
void dispose_ship(ship_t *ship);

#endif //__SHIP_H

