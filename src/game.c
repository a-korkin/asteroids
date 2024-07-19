#include "game.h"
#include "ship.h"
#include <SDL2/SDL.h>
#include <stdio.h>

ship_t *ship;

state_t *init(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "ERROR initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    state_t *state = (state_t *) malloc(sizeof(state_t));
    if (!state) {
        fprintf(stderr, 
                "ERROR allocating memory for state: %s\n", SDL_GetError());
        exit(1);
    }
    state->window = SDL_CreateWindow(
            "Asteroids", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            SCREEN_W, 
            SCREEN_H, 
            SDL_WINDOW_SHOWN);
    if (!state->window) {
        fprintf(stderr, "ERROR creating window: %s\n", SDL_GetError());
        exit(1);
    }
    state->renderer = SDL_CreateRenderer(
            state->window, -1, SDL_RENDERER_SOFTWARE);
    if (!state->renderer) {
        fprintf(stderr, "ERROR creating renderer: %s\n", SDL_GetError());
        exit(1);
    }
    state->running = true;

    return state;
}


ship_t *create_ship(void) {
    ship_t *ship = (ship_t *) malloc(sizeof(ship_t));
    if (!ship) {
        fprintf(stderr, 
                "ERROR allocating memory for ship: %s\n", SDL_GetError());
        exit(1);
    }
    return ship;
}

void handle_events(state_t *state) {
    SDL_PollEvent(&state->event);
    if (state->event.type == SDL_QUIT) {
        state->running = false;
    }
    if (state->event.type == SDL_KEYDOWN) {
        switch (state->event.key.keysym.sym) {
            case SDLK_ESCAPE: state->running = false;
        }
    }
}

void dispose(state_t *state) {
    dispose_ship(ship);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}

void draw_background(state_t *state) {
    if (SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0x00, 0xFF) < 0) {
        fprintf(stderr, "ERROR set draw color: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(state->renderer);
}

void draw(state_t *state) {
    draw_background(state);
    draw_ship(state, ship);
    SDL_RenderPresent(state->renderer);
}

void loop(state_t *state) {
    while (state->running) {
        handle_events(state);
        draw(state);
    }
}

void run(void) {
    state_t *state = init();
    ship = create_ship();
    SDL_FPoint center = { SCREEN_W/2.0f, SCREEN_H/2.0f };
    SDL_FPoint points[4] = {
        { center.x + 10, center.y + 10 },
        { center.x + 20, center.y + 50 }, 
        { center.x, center.y + 50 },
        { center.x + 10, center.y + 10 },
    };
    ship->points = points;
    loop(state);
    dispose(state);
}

