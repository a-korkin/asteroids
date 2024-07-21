#include "game.h"
#include "ship.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <time.h>

ship_t *ship;
int last_frame_time;

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
    last_frame_time = SDL_GetTicks();

    return state;
}

ship_t *create_ship(void) {
    ship_t *ship = (ship_t *) malloc(sizeof(ship_t));
    if (!ship) {
        fprintf(stderr, 
                "ERROR allocating memory for ship: %s\n", SDL_GetError());
        exit(1);
    }
    ship->angle = 0;
    return ship;
}

float get_delta_time(void) {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
    return delta_time;
}

void pew(ship_t *ship) {
    bullet_t *bullet = (bullet_t *) malloc(sizeof(bullet_t));
    if (!bullet) {
        fprintf(stderr, 
            "ERROR couldn't allocate memory for bullet: %s\n", SDL_GetError());
        exit(1);
    }
    bullet->show = true;
    bullet->angle = ship->angle;
    bullet->position.x = ship->points[1].x;
    bullet->position.y = ship->points[1].y;
    if (!ship->bullets) {
        ship->bullets = bullet;
        ship->last_bullet = bullet;
    }
    if (ship->last_bullet) {
        bullet->prev = ship->last_bullet;
        ship->last_bullet->next = bullet;
        bullet->next = NULL;
    }
    ship->last_bullet = bullet;
   
    fprintf(stdout, "angle: %.2f, x: %.2f, y: %.2f\n", 
            bullet->angle, bullet->position.x, bullet->position.y);
}

void update(void) {
    float delta_time = get_delta_time();
    update_bullets(delta_time, ship->bullets);
}

void handle_events(state_t *state) {
    SDL_PollEvent(&state->event);
    float delta_time = get_delta_time();
    if (state->event.type == SDL_QUIT) {
        state->running = false;
    }
    if (state->event.type == SDL_KEYDOWN) {
        switch (state->event.key.keysym.sym) {
            case SDLK_ESCAPE: state->running = false; break;
            case SDLK_RIGHT: rotate_ship(ship, ROT_RIGHT); break;
            case SDLK_LEFT: rotate_ship(ship, ROT_LEFT); break;
            case SDLK_SPACE: pew(ship);
        }
    }
    if (state->event.key.keysym.sym == SDLK_UP) {
        if (state->event.key.state == SDL_PRESSED && !ship->engine_work) {
            ship->engine_work = true;
            ship->start = SDL_GetTicks();
        }
        if (state->event.key.state == SDL_RELEASED && ship->engine_work) {
            ship->engine_work = false;
            ship->end = SDL_GetTicks();
            // fprintf(stdout, "start: %d, end: %d, diff: %d\n",
            //         ship->start, ship->end, ship->end - ship->start);
            move_ship(delta_time, ship);
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
    draw_bullets(state, ship);
    SDL_RenderPresent(state->renderer);
}

void loop(state_t *state) {
    while (state->running) {
        handle_events(state);
        update();
        draw(state);
    }
}

void run(void) {
    state_t *state = init();
    ship = create_ship();
    SDL_FPoint center = { SCREEN_W/2.0f, SCREEN_H/2.0f };
    SDL_FPoint _points[SHIP_POINTS] = {
        { center.x, center.y + 50 },        // ship
        { center.x + 10, center.y + 10 },   // peak
        { center.x + 20, center.y + 50 }, 
        { center.x + 2, center.y + 45 },    // engine base
        { center.x + 18, center.y + 45},
        { center.x + 6, center.y + 45 },    // flame small
        { center.x + 10, center.y + 53 },
        { center.x + 14, center.y + 45 },
        { center.x + 10, center.y + 30},    // center of ship
    };
    ship->points = _points;
    ship->engine_work = false;
    loop(state);
    dispose(state);
}

