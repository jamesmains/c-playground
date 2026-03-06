#ifndef CONFIG_H
#define CONFIG_H
#define MAX_PLAYERS 32

#include <SDL2/SDL.h>

typedef struct PlayerState{
    int id;
    float x,y;
    int map_id;
    int active;
    int w, h;
    SDL_Color color;
} PlayerState;

typedef struct {
    PlayerState players[MAX_PLAYERS];
} SharedContext;

#endif