#ifndef ITEMS_H
#define ITEMS_H

#include <stdbool.h>
#include "stats.h"

typedef enum {
    USE,
    CASTS,
    DURABLE,
} UseType;

struct Entity;
typedef struct Entity Entity;

struct Item;
typedef struct Item Item;

typedef struct {
    int dice_sides;
    int dice_count;
    int attribute_id;
} DiceRoll;

typedef void (*ItemEffect)(Entity *user, Entity *target, const Item *item);


typedef struct {
    int stat_id;
    int required_value;
} Requirement;

typedef struct Item{
    char name[32];
    int id;
    int item_shop_cost;
    Requirement requirements[3];
    int requirement_count;

    int max_uses;
    int uses_remaining; // If reaches 0, removed from users inventory
    UseType use_type; // For display only (i.e. Scrolls may have 5 'casts' remaning while a sword is 'durable')

    int action_cost;
    int bonus_action_cost;

    DiceRoll rolls[3];
    int dice_roll_count;
    ItemEffect effect;
} Item;

void use_item(const Item *item, Entity *user, Entity *target);
bool default_requirement_check(Entity *user, Stat *requirements[], const Item *item);
int default_dice_roll(DiceRoll *roll, const Item *item);
void physical_damage_effect(Entity *user, Entity *target, const Item *item);
void magic_damage_effect(Entity *user, Entity *target, const Item *item);

#endif