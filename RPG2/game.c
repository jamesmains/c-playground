#include "game.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#include <string.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void await_user()
{
    printf("Press Enter to continue...\n");
    fflush(stdin);
    getchar();
}

char get_input()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar(); // Grabs the key immediately

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore settings
    return ch;
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

void handle_ai(GameContext *ctx)
{
    Map *map = &ctx->current_map;
    for (int e = 0; e < map->enemy_count; e++)
    {
        // Point directly to the enemy in the map
        MapEnemy *m_enemy = &map->enemies[e];
        if(m_enemy->is_alive == false)
        {
            continue;
        }
        int steps = (m_enemy->enemy_data.stats[STAT_DEX].current_value - 10) / 2;
        if (steps < 1)
        steps = 1;
        for(int s = 0; s < steps; s++)
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

void handle_explore(GameContext *ctx)
{
    draw_world(ctx);

    // Handle player's turn
    Entity player = *ctx->player;
    int steps = (player.stats[STAT_DEX].current_value - 10) / 2;
    if (steps < 1)
    steps = 1;
    bool enemy_encountered = false;
    printf("Steps remaining: %d\n", steps);
    for (int i = 0; i < steps; i++)
    {
        get_player_input(ctx);
        draw_world(ctx);
        printf("Steps remaining: %d\n", steps - i - 1);

        for (int i = 0; i < ctx->current_map.enemy_count; i++)
        {
            Entity *player = ctx->player;
            Entity *enemy = &ctx->current_map.enemies[i].enemy_data;
            if (player->x == enemy->x && player->y == enemy->y && ctx->current_map.enemies[i].is_alive == true)
            {
                ctx->state = STATE_COMBAT;
                ctx->current_enemy_index = i;
                enemy_encountered = true;
            }
        }
        if (enemy_encountered == true)
        {
            break;
        }
    }
    if (enemy_encountered == true)
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

void handle_combat(GameContext *ctx)
{
    printf("\033[H\033[J");
    printf("===========================================\n");
    printf("%s | Health: %d/%d\n", ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.name, ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.stats[STAT_VIT].current_value, ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.stats[STAT_VIT].base_value);
    printf("===========================================\n");
    printf("%s | Health: %d/%d\n", ctx->player->name, ctx->player->stats[STAT_VIT].current_value, ctx->player->stats[STAT_VIT].base_value);
    printf("===========================================\n");

    ctx->player->combat_logic(ctx->player, &ctx->current_map.enemies[ctx->current_enemy_index].enemy_data, NULL);
    await_user();

    // Player's turn
    // Show Base Menu
    // |-> Wait for valid action to be selected

    // Check if enemy is dead
    if (ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.stats[STAT_VIT].current_value <= 0)
    {
        printf("%s defeated!\n", ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.name);
        ctx->state = STATE_EXPLORE;
        ctx->current_map.enemies[ctx->current_enemy_index].is_alive = false;
        win_match(ctx->player, &ctx->current_map.enemies[ctx->current_enemy_index].enemy_data);
        await_user();
        return;
    }

    // Enemy's turn
    ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.combat_logic(&ctx->current_map.enemies[ctx->current_enemy_index].enemy_data, ctx->player, NULL);
    await_user();

    // Check if player is dead
}

void game_loop(GameContext *ctx)
{
    if (ctx->state == STATE_EXPLORE)
    {
        handle_explore(ctx);
        // Handle player's turn

        // printf("%d, player x: %d, player y: %d", ctx->state, ctx->player->x, ctx->player->y);
        // await_user();
    }
    else if (ctx->state == STATE_COMBAT)
    {
        printf("Debug: Entering combat state\n");
        handle_combat(ctx);
    }
    // Item i = shop_items[2];
    // Entity e = monster_pool[0];
    // printf("\nItem: %s\n", i.name);
    // printf("Monster: %s\n", e.name);
    // if (i.effect != NULL)
    // {
    //     i.effect(ctx->player, &e, &i);
    // }
}