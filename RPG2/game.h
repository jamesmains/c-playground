#ifndef GAME_H
#define GAME_H

#include "entities.h"
#include "world.h"

typedef enum {
    STATE_EXPLORE,
    STATE_COMBAT,
    STATE_SHOP,
    STATE_QUIT
} GameState;

struct Map; 
typedef struct Map Map;

typedef struct GameContext {
    Entity *player;
    int current_enemy_index;
    int current_shop_index;
    Map current_map;
    GameState state;
} GameContext;

void game_loop(GameContext *ctx);
void await_user();
char get_input();

#endif