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
    if (SDL_RenderDrawLinesF(state->renderer, ship->points, 4) < 0) {
        fprintf(stderr, "ERROR draw lines for ship: %s\n", SDL_GetError());
        exit(1);
    }
}

void dispose_ship(ship_t *ship) {
    free(ship);
}

