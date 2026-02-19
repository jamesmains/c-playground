#include "combat.h"
#include "entities.h"
#include "game.h"
#include <stdio.h>

void draw_combat_screen(GameContext *ctx){
    printf("\033[H\033[J");
    printf("===========================================\n");
    printf("%s | Health: %d/%d\n", ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.name, ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.stats[STAT_VIT].current_value, ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.stats[STAT_VIT].base_value);
    printf("===========================================\n");
    printf("%s | Health: %d/%d\n", ctx->player->name, ctx->player->stats[STAT_VIT].current_value, ctx->player->stats[STAT_VIT].base_value);
    printf("===========================================\n");
}

void handle_combat(GameContext *ctx)
{
    draw_combat_screen(ctx);

    ctx->player->combat_logic(ctx->player, &ctx->current_map.enemies[ctx->current_enemy_index].enemy_data, NULL);
    await_user();

    // Player's turn
    // Show Base Menu
    // |-> Wait for valid action to be selected

    // Check if enemy is dead
    if (ctx->current_map.enemies[ctx->current_enemy_index].enemy_data.stats[STAT_VIT].current_value <= 0)
    {
        printf("\033[H\033[J");
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