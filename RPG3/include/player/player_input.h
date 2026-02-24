#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <SDL2/SDL.h>

struct NetworkPlayer; 
typedef struct NetworkPlayer NetworkPlayer;

void handle_input(NetworkPlayer *player, SDL_Event *event);

#endif