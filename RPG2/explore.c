#include "explore.h"
#include "world.h"
#include "database.h"
#include "game.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void handle_ai(GameContext *ctx)
{
    Map *map = &ctx->current_map;
    for (int e = 0; e < map->enemy_count; e++)
    {
        // Point directly to the enemy in the map
        MapEnemy *m_enemy = &map->enemies[e];
        if (m_enemy->is_alive == false)
        {
            continue;
        }
        int steps = get_stat_modifier(&m_enemy->enemy_data, STAT_DEX, 1);
        for (int s = 0; s < steps; s++)
        {
            // Simple AI: Move towards the player if not on the same tile
            // Use the x/y stored inside the entity stats
            int ex = m_enemy->enemy_data.x;
            int ey = m_enemy->enemy_data.y;

            int move_x = ctx->player->x > ex ? 1 : ctx->player->x < ex ? -1
                                                                       : 0;
            int move_y = ctx->player->y > ey ? 1 : ctx->player->y < ey ? -1
                                                                       : 0;

            // Pass the address of the internal entity stats
            move_entity(&m_enemy->enemy_data, map, move_x, move_y);
            draw_world(ctx);
            SLEEP_MS(50);
        }
    }
}

void get_player_input(GameContext *ctx)
{
    Map *map = &ctx->current_map;
    char c = get_input();
    int move_dir_y = 0;

    if (c == 'w')
        move_dir_y = -1;
    else if (c == 's')
        move_dir_y = 1;

    int move_dir_x = 0;

    if (c == 'd')
        move_dir_x = 1;
    else if (c == 'a')
        move_dir_x = -1;
    Entity player = *ctx->player;
    if (move_dir_x != 0 || move_dir_y != 0)
    {
        int next_x = player.x + move_dir_x;
        int next_y = player.y + move_dir_y;
        for (int d = 0; d < 4; d++)
        {
            Door door = map->doors[d];
            if (door.x == next_x && door.y == next_y)
            {
                set_map(ctx, maps[door.leads_to_map_id]);
                ctx->player->x = door.dest_x;
                ctx->player->y = door.dest_y;
                return;
            }
        }
    }

    move_entity(ctx->player, map, move_dir_x, move_dir_y);
}

void handle_explore(GameContext *ctx)
{
    draw_world(ctx);

    // Handle player's turn
    Entity player = *ctx->player;
    int steps = get_stat_modifier(&player, STAT_DEX, 1);
    bool enemy_encountered = false;
    bool shop_entered = false;
    printf("Steps remaining: %d\n", steps);
    for (int i = 0; i < steps; i++)
    {
        get_player_input(ctx);
        draw_world(ctx);
        printf("Steps remaining: %d\n", steps - i - 1);
        Entity *player = ctx->player;
        for (int i = 0; i < ctx->current_map.enemy_count; i++)
        {

            Entity *enemy = &ctx->current_map.enemies[i].enemy_data;
            if (player->x == enemy->x && player->y == enemy->y && ctx->current_map.enemies[i].is_alive == true)
            {
                ctx->state = STATE_COMBAT;
                ctx->current_enemy_index = i;
                enemy_encountered = true;
            }
        }
        if (ctx->current_map.shop_id != -1)
        {
            if (ctx->current_map.data[player->y][player->x] == '$')
            {
                printf("Entering shop...\n");
                ctx->state = STATE_SHOP;
                ctx->current_shop_index = ctx->current_map.shop_id; // Only one shop per map for now, so this is always 0 but can be used for multiple shops later
                shop_entered = true;
                return;
            }
        }

        if (enemy_encountered == true || shop_entered == true)
        {
            break;
        }
    }
    if (enemy_encountered == true || shop_entered == true)
    {
        return;
    }
    // Handle ai's turn
    handle_ai(ctx);
    for (int i = 0; i < ctx->current_map.enemy_count; i++)
    {
        Entity *player = ctx->player;
        Entity *enemy = &ctx->current_map.enemies[i].enemy_data;
        if (player->x == enemy->x && player->y == enemy->y && ctx->current_map.enemies[i].is_alive == true)
        {
            ctx->state = STATE_COMBAT;
            ctx->current_enemy_index = i;
        }
    }
}