#include "world.h"
#include <stdio.h>
const char *world_1[] = {
    "=================",
    "|               |",
    "|=|             |",
    "|     |=|       |",
    "|               |",
    "|       |=|     |",
    "|               |",
    "|   |=|         |",
    "|               |",
    "=================",
    NULL
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

void move_entity(Entity *entity, Map *map, int move_horizontal, int move_vertical){
    int next_x = entity->x + move_horizontal;
    int next_y = entity->y + move_vertical;

    // Clamp
    if(next_y < 0 || next_y >= map-> height){
        next_y = entity->y;
    }
    if(next_x < 0 || next_x >= map-> width ){
        next_x = entity->x;
    }
    // Check if they're unable to move due to map bounds, if so return out
    if(next_y == entity->y && next_x == entity->x){
        return;
    }

    char target_tile = map->data[next_x][next_y];
    // Check if open or grass
    if(target_tile == ' ' || target_tile == '.'){
        entity->x = next_x;
        entity->y = next_y;
    }
}