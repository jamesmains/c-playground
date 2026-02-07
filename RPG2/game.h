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

typedef struct {
    Entity *player;
    const Map *current_map;
    GameState state;
} GameContext;

void game_loop(GameContext *ctx);

#endif