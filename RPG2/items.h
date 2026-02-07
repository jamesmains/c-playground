#ifndef ITEMS_H
#define ITEMS_H

#include <stdbool.h>
#include "stats.h"

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
    Requirement requirements[3];
    int requirement_count;

    DiceRoll rolls[3];
    int dice_roll_count;
    ItemEffect effect;
} Item;

bool default_requirement_check(Entity *user, Stat *requirements[], const Item *item);
int default_dice_roll(DiceRoll *roll, const Item *item);
void physical_damage_effect(Entity *user, Entity *target, const Item *item);

#endif