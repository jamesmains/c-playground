#include "world.h"
#include <stdio.h>
#include "database.h"
const char *world_1[] = {
    "=================",
    "|               |",
    "|=|             |",
    "|     |=|       |",
    "|               |",
    "|               |",
    "|               |",
    "|               |",
    "|               |",
    "=================",
};

const Map map_1 = {
    .data = world_1,
    .height = 10,
    .width = 17,
    .map_name = "Test Dungeon"
};

void draw_world(const Map *map, int player_x, int player_y) {
    printf("\033[H\033[J");
    for(int y = 0; y < map->height; y++) {
        if (y == player_y) {
            // If the player is on this line, we have to do it the hard way (char by char)
            for(int x = 0; x < map->width; x++) {
                if(x == player_x) printf("@");
                else printf("%c", map->data[y][x]);
            }
        } else {
            // Otherwise, just print the whole string fast
            printf("%s", map->data[y]);
        }
        printf("\n");
    }
}

void move_entity(Entity *entity, const Map *map, int move_horizontal, int move_vertical)
{
    int next_x = entity->x + move_horizontal;
    int next_y = entity->y + move_vertical;

    // Check map bounds (Clamp)
    if (next_y < 0) next_y = 0;
    if (next_y >= map->height) next_y = map->height - 1;
    if (next_x < 0) next_x = 0;
    if (next_x >= map->width) next_x = map->width - 1;

    // Get the target tile
    char target_tile = map->data[next_y][next_x];

    // Check for collision
    // Not sure which approach I like better, basically the same thing so I guess it depends on which
    // list grows the least should be used.
    // Blacklist: '|' & '='
    if (target_tile != '|' && target_tile != '=')
    {
        entity->x = next_x;
        entity->y = next_y;
    }

    // Whitelist: ' ' & '.'
    // if (target_tile == ' ' || target_tile == '.')
    // {
    //     entity->x = next_x;
    //     entity->y = next_y;
    // }
}