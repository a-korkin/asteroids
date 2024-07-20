#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

#define SCREEN_W 640
#define SCREEN_H 480
#define FPS 60
#define FRAME_TARGET_TIME (1000.0f/FPS)
#define PI 3.141592654

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool running;
} state_t;

state_t *init(void);
void handle_events(state_t *state);
void dispose(state_t *state);
void draw_background(state_t *state);
void draw(state_t *state);
void loop(state_t *state);
void run(void);

#endif // __GAME_H

