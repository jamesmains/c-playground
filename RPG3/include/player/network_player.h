#ifndef NETWORK_PLAYER_H
#define NETWORK_PLAYER_H

#include <SDL2/SDL.h>

typedef struct NetworkPlayer
{
    int id;
    float x, y;
    int w, h;
    SDL_Color color;
    int active; // 0 = not active, 1 = active
    int map_id;
    char name[16];
} NetworkPlayer;

void handle_player_join();

void handle_player_leave();

#endif