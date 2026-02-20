#include "world.h"
#include <stdio.h>
#include "database.h"
#include <stdlib.h>

void draw_world(GameContext *ctx){
    Map *map = &ctx->current_map;
    int player_x = ctx->player->x;
    int player_y = ctx->player->y;
    printf("\033[H\033[J");
    printf(" ~[%s]~\n", map->map_name);
    for(int y = 0; y < map->height; y++) {
        
        for (int x = 0; x < map->width; x++){
            
            if(x == player_x && y == player_y){
                printf("@");
            } 
            else {
                bool monster_here = false;
                bool door_here = false;

                for (int e = 0; e < map->enemy_count; e++){
                    if(map->enemies[e].enemy_data.x == x && map->enemies[e].enemy_data.y == y && map->enemies[e].is_alive == true){
                        printf("M");
                        monster_here = true;
                        break;
                    }
                }

                for (int d = 0; d < map->door_count; d++)
                {
                    if (map->doors[d].x == x && map->doors[d].y == y)
                    {
                        printf("D");
                        door_here = true;
                        break;
                    }
                }

                if(!monster_here && !door_here){
                    char tile = map->data[y][x];
                    printf("%c", (tile == 'M') ? ' ' : tile);
                }
            }
            
            if (y == 0 && x == map->width - 1) {
                printf(" %s HP: %d/%d, Gold: %d",ctx->player->name, ctx->player->stats[STAT_VIT].current_value, ctx->player->stats[STAT_VIT].base_value, ctx->player->gold);
            }
            else if (y == 1 && x == map->width - 1) {
                printf(" Level: %d | EXP: %d/%d", ctx->player->level, ctx->player->current_exp, ctx->player->exp_to_next_level);
            } 
            else if (y == 2 && x == map->width - 1) {
                printf(" STR: %d | DEX: %d | INT: %d | END: %d", ctx->player->stats[STAT_STR].current_value, ctx->player->stats[STAT_DEX].current_value, ctx->player->stats[STAT_INT].current_value, ctx->player->stats[STAT_END].current_value);
            }
            else if (y == 3 && x == map->width -1){
                printf(" CORDS | X:%d, Y:%d", ctx->player->x,ctx->player->y);
            }
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
        printf("Moving %s to x: %d, y:%d", entity->name, entity->x, entity->y);
    }
    else printf("Cannot move! %s stuck at x: %d, y:%d", entity->name,entity->x, entity->y);

    // Whitelist: ' ' & '.'
    // if (target_tile == ' ' || target_tile == '.')
    // {
    //     entity->x = next_x;
    //     entity->y = next_y;
    // }
}

void set_map(GameContext *ctx, Map map){
    ctx->current_map = map;
    init_map(ctx);
}

void init_map(GameContext *ctx){
    // Initialize enemies
    Map *map = &ctx->current_map;
    map->enemy_count = 0;
    for (int y = 0; y < map->height; y++){
        for (int x = 0; x < map->width; x++){
            if(map->data[y][x] == 'M' && map->enemy_count < ENEMY_PER_FLOOR){
                int enemy_index = map->enemy_count;

                map->enemies[enemy_index].enemy_data = map->enemy_pool[(rand() % map->enemy_pool_count)];
                map->enemies[enemy_index].enemy_data.x = x;
                map->enemies[enemy_index].enemy_data.y = y;
                map->enemies[enemy_index].is_alive = true;
                map->enemy_count++;
            }
        }
    }

}