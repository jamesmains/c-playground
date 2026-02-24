#ifndef ENGINE_H
#define ENGINE_H
#include "network.h"
#include "player/network_player.h"

typedef struct GameContext{
    NetworkPlayer players[4];
    int my_client_id;
    int running;
} GameContext;

void initialize_engine();
void main_loop();
#endif