#include <SDL2/SDL.h>
#include <stdio.h>
#include "cJSON.h"
#include "player/network_player.h"
#include "player/player_input.h"
#include "network.h"
#include "engine.h"

int my_client_id = -1;


// Global Game State
// Todo: This is a temporary global context to hold player states. In a real game, you'd want a more robust system for managing players and their states.
GameContext ctx = {
    .players = {
        {.x = 100, .y = 200, .w = 40, .h = 40, .color = {0, 255, 100, 255}}, // Green (You)
        {.x = 300, .y = 200, .w = 40, .h = 40, .color = {255, 100, 0, 255}},  // Orange (Other)
        {.x = 300, .y = 200, .w = 40, .h = 40, .color = {255, 100, 0, 255}},  // Orange (Other)
        {.x = 300, .y = 200, .w = 40, .h = 40, .color = {255, 100, 0, 255}},  // Orange (Other)
    },
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