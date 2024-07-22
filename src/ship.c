#include "ship.h"
#include "game.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <math.h>

void draw_ship(state_t *state, ship_t *ship) {
    if (SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0) {
        fprintf(stderr, "ERROR render color ship: %s\n", SDL_GetError());
        exit(1);
    }
    // Draw V
    if (SDL_RenderDrawLinesF(state->renderer, ship->points, 3) < 0) {
        fprintf(stderr, "ERROR draw lines for ship: %s\n", SDL_GetError());
        exit(1);
    }
    // Draw engine base
    // 3,4
    if (SDL_RenderDrawLineF(state->renderer, 
                ship->points[3].x, ship->points[3].y,
                ship->points[4].x, ship->points[4].y) < 0) {
        fprintf(stderr, "ERROR draw line for ship engine: %s\n", SDL_GetError());
        exit(1);
    }
    // Flame small
    if (ship->engine_work) {
        if (SDL_RenderDrawLinesF(state->renderer, ship->points + 5, 3) < 0) {
            fprintf(stderr, "ERROR draw line flame small: %s\n", SDL_GetError());
            exit(1);
        }
    }
}

void draw_bullets(state_t *state, ship_t *ship) {
    bullet_t *bullet = ship->bullets;
    while (bullet) {
        if (bullet->show) {
            if (SDL_RenderDrawPointF(
                        state->renderer, 
                        bullet->position.x, bullet->position.y) < 0) {
                fprintf(stderr, "ERROR draw bullet: %s\n", SDL_GetError());
                exit(1);
            }
        }
        bullet = bullet->next;
    }
}

void rotate_ship(ship_t *ship, rotation_t rot) {
    float degree = ROTATION_ANGLE * rot;
    float result;
    degree = (degree * PI) / 180;

    for (int i = 0; i < SHIP_POINTS; i++) {
        float x = ship->points[i].x - ship->points[SHIP_POINTS-1].x;
        float y = ship->points[i].y - ship->points[SHIP_POINTS-1].y;
        ship->points[i].x = (x * cos(degree) - y * sin(degree)) 
            + ship->points[SHIP_POINTS-1].x;
        ship->points[i].y = (x * sin(degree) + y * cos(degree)) 
            + ship->points[SHIP_POINTS-1].y;
    }
    ship->angle += degree;
}

void drop_bullets(bullet_t *bullets) {
    bullet_t *bullet = bullets;
    while (bullet && !bullet->show) {
        if (bullet->prev && bullet->next) {
            bullet->prev->next = bullet->next;
            bullet->next->prev = bullet->prev;
        }
        // free(bullet);
        bullet = bullet->next;
    }
}

void update_bullets(float delta_time, bullet_t *bullets) {
    bullet_t *bullet = bullets;
    while (bullet) {
        if (bullet->position.x <= 20 
            || bullet->position.x >= SCREEN_W - 20
            || bullet->position.y <= 20
            || bullet->position.y >= SCREEN_H - 20) {
            bullet->show = false;
        } 
        bullet->position.x += BULLET_SPEED * sin(bullet->angle);
        bullet->position.y -= BULLET_SPEED * cos(bullet->angle);
        bullet = bullet->next;
    }
    // drop_bullets(bullets);
}

void move_ship(float delta_time, ship_t *ship) {
    for (int i = 0; i < SHIP_POINTS; i++) {
        ship->points[i].x += SHIP_SPEED * sin(ship->angle);
        ship->points[i].y -= SHIP_SPEED * cos(ship->angle);
    }
}

void dispose_ship(ship_t *ship) {
    free(ship);
}

