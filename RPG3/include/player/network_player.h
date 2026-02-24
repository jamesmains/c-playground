#ifndef NETWORK_PLAYER_H
#define NETWORK_PLAYER_H

#include <SDL2/SDL.h>

typedef struct NetworkPlayer
{
    int id;
    float x, y;
    int w, h;
    SDL_Color color;
    int grid_cell_id;
    char name[16];
} NetworkPlayer;

#endif