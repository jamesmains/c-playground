#include "game.h"
#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void draw_shop_screen(GameContext *ctx){
    printf("\033[H\033[J");
    printf("Welcome to %s!\n", shops[ctx->current_shop_index].name);
    printf("%s\n", shops[ctx->current_shop_index].description);
    printf("Items for sale:\n");
}

void handle_shop(GameContext *ctx)
{
    draw_shop_screen(ctx);
    await_user();
}