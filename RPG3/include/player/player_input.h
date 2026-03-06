#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <SDL2/SDL.h>

struct PlayerState; 
typedef struct PlayerState PlayerState;

void input_loop();
void handle_input(PlayerState *player, SDL_Event *event);

#endif