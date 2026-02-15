#ifndef WORLD_H
#define WORLD_H
#define ENEMY_PER_FLOOR 3

#include "entities.h"


typedef struct {
    Entity enemy_data;
    int x;
    int y;
    bool is_alive;
} MapEnemy;

typedef struct {
    int x, y;               // Location of the door on the current map
    int leads_to_map_id;    // ID of the map this door leads to
    int dest_x, dest_y;     // Where the player lands on the new map
} Door;

typedef struct Map{
    const char **data;
    int width;
    int height;
    Entity enemy_pool[ENEMY_PER_FLOOR];
    int enemy_pool_count;
    const char *map_name;

    MapEnemy enemies[ENEMY_PER_FLOOR];
    int enemy_count;

    Door doors[4]; // Up to 4 doors per map to keep it simple, can be empty if no doors
    int door_count;
} Map;

#include "game.h"

struct GameContext;
typedef struct GameContext GameContext;

void draw_world(GameContext *ctx);
void move_entity(Entity *entity, const Map *map, int move_horizontal, int move_vertical);
void set_map(GameContext *ctx, Map map);
void init_map(GameContext *ctx);
#endif