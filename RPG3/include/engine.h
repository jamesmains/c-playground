#ifndef ENGINE_H
#define ENGINE_H
#include "network.h"
#include "player/network_player.h"
#include "common.h"

typedef struct GameContext{
    SharedContext shared;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int my_client_id;
    int running;
} GameContext;

void initialize_engine();
void main_loop();
#endif