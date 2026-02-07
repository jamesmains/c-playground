#ifndef WORLD_H
#define WORLD_H

#include "entities.h"

typedef struct{
    const char **data;
    int width;
    int height;
    Entity test_map_enemy;
    const char *map_name;
} Map;

extern const Map map_1;

void draw_world(const Map *map, int player_x, int player_y);
void move_entity(Entity *entity, const Map *map, int move_horizontal, int move_vertical);
#endif