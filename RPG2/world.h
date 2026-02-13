#ifndef WORLD_H
#define WORLD_H
#define ENEMY_PER_FLOOR 3

#include "entities.h"
#include "game.h"

struct GameContext;
typedef struct GameContext GameContext;

typedef struct {
    Entity enemy_data;
    int x;
    int y;
    bool is_alive;
} MapEnemy;

typedef struct Map{
    const char **data;
    int width;
    int height;
    Entity test_map_enemy;
    const char *map_name;

    MapEnemy enemies[ENEMY_PER_FLOOR];
    int enemy_count;
} Map;

extern Map map_1;

void draw_world(GameContext *ctx);
void move_entity(Entity *entity, const Map *map, int move_horizontal, int move_vertical);
void set_map(GameContext *ctx, Map *map);
#endif