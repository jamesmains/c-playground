#include <SDL2/SDL.h>
#include <stdio.h>
#include "cJSON.h"
#include "player/network_player.h"
#include "player/player_input.h"
#include "network.h"
#include "engine.h"


// Global Game State
// Todo: This is a temporary global context to hold player states. In a real game, you'd want a more robust system for managing players and their states.
GameContext ctx = {
    .my_client_id = -1,
    .running = 1
};


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    initialize_websocket();
    initialize_engine();

#ifndef __EMSCRIPTEN__
    while (ctx.running)
    {
        main_loop(&ctx);
        SDL_Delay(16);
    }
#endif

    return 0;
}