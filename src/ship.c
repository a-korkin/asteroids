#include "ship.h"
#include "game.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>


ship_t *create_ship(void) {
    ship_t *ship = (ship_t *) malloc(sizeof(ship_t));
    if (!ship) {
        fprintf(stderr, 
                "ERROR allocating memory for ship: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FPoint center = { SCREEN_W/2.0f, SCREEN_H/2.0f };
    SDL_FPoint points[3] = {
        { center.x + 10, center.y + 10 },
        { center.x + 20, center.y + 50 }, 
        { center.x, center.y + 50 },
    };
    ship->points = points;
    return ship;
}

void draw_ship(state_t *state, ship_t *ship) {
    if (SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0) {
        fprintf(stderr, "ERROR render color ship: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderDrawLinesF(state->renderer, ship->points, 3) < 0) {
        fprintf(stderr, "ERROR draw lines for ship: %s\n", SDL_GetError());
        exit(1);
    }
}

void dispose_ship(ship_t *ship) {
    free(ship);
}

