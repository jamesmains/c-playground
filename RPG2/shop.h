#ifndef SHOP_H
#define SHOP_H
#define SHOP_ITEM_COUNT 5

#include "items.h"

struct GameContext;
typedef struct GameContext GameContext;

typedef struct {
    int id;
    char name[32];
    char description[128];
    Item shop_items[SHOP_ITEM_COUNT];
    int item_count;

} Shop;

void draw_shop_screen(GameContext *ctx);
void handle_shop(GameContext *ctx);

#endif