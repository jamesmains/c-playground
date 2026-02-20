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
    printf("=================================\n");
    printf("ID | Item Name\n");
    Shop shop = shops[ctx->current_shop_index];
    for(int i = 0; i < shop.item_count; i++){
        printf("%d. %s\t ...%d gold\n", i +1, shop.shop_items[i].name, shop.shop_items[i].item_shop_cost);
    }
    printf("=================================\n");
    printf("Your Gold: %d\n", ctx->player->gold);
    printf("Enter the ID of the item you wish to purchase, or 0 to exit: ");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n');
    if(choice > 0 && choice <= shop.item_count){
        Item *selected = &shop.shop_items[choice - 1];
        if(ctx->player->gold >= selected->item_shop_cost){
            ctx->player->gold -= selected->item_shop_cost;
            add_item(ctx->player, *selected);
            printf("You purchased %s!\n", selected->name);
        } else {
            printf("You don't have enough gold to purchase %s!\n", selected->name);
        }
    } else {
        printf("Exiting shop.\n"); 
        ctx->state = STATE_EXPLORE;
    }

}

void handle_shop(GameContext *ctx)
{
    draw_shop_screen(ctx);
    await_user();
}