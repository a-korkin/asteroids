#include "ship.h"
#include "game.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

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

void rotate_ship(ship_t *ship, rotation_t rot) {
    double arg = 15 * rot;
    double result;
    arg = (arg * PI) / 180;
    result = cos(arg) * rot;

    for (int i = 0; i < SHIP_POINTS; i++) {
        float x = ship->points[i].x - ship->points[SHIP_POINTS-1].x;
        float y = ship->points[i].y - ship->points[SHIP_POINTS-1].y;
        ship->points[i].x = (x * cos(arg) - y * sin(arg)) 
            + ship->points[SHIP_POINTS-1].x;
        ship->points[i].y = (x * sin(arg) + y * cos(arg)) 
            + ship->points[SHIP_POINTS-1].y;
    }
}

void dispose_ship(ship_t *ship) {
    free(ship);
}

