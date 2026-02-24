#include "../include/player/player_input.h"
#include "../include/player/network_player.h"
#include <SDL2/SDL.h>

// Take in the player, the event, and update the player's target position
void handle_input(NetworkPlayer *player, SDL_Event *event)
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