#include "game.h"

state_t *init(void) {
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
    state->running = 1;

    return state;
}

void handle_events(state_t *state) {
    SDL_PollEvent(&state->event);
    if (state->event.type == SDL_QUIT) {
        state->running = 0;
    }
    if (state->event.type == SDL_KEYDOWN) {
        switch (state->event.key.keysym.sym) {
            case SDLK_ESCAPE: state->running = 0;
        }
    }
}

void dispose(state_t *state) {
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
    loop(state);
    dispose(state);
}

