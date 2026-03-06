#include "../include/player/player_input.h"
#include "../include/player/network_player.h"
#include <SDL2/SDL.h>
#include "engine.h"
#include "main.h"

void input_loop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            ctx.running = 0;

        // If Keydown, fire handle function
        if (event.type == SDL_KEYDOWN)
        {
            handle_input(&ctx.shared.players[ctx.my_client_id], &event);
        }
    }
}

// Take in the player, the event, and update the player's target position
void handle_input(PlayerState *player, SDL_Event *event)
{
    // Get the key that was pressed
    SDL_Keycode key = event->key.keysym.sym;

    // Get horizontal input
    player->x = key == SDLK_a || key == SDLK_LEFT ? player->x - 10 : key == SDLK_d || key == SDLK_RIGHT ? player->x + 10
                                                                                                        : player->x;
    // Get vertical input
    player->y = key == SDLK_w || key == SDLK_UP ? player->y - 10 : key == SDLK_s || key == SDLK_DOWN ? player->y + 10
                                                                                                     : player->y;
}