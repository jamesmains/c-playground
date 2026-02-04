#ifndef ENTITIES_H
#define ENTITIES_H
#define INVENTORY_SIZE 20

// Include because full definition of Item is needed in Entity struct
#include "items.h"
#include "stats.h"

// Forward declare because of circular dependency
struct Entity;
typedef struct Entity Entity;

//typedef void (*EntityStats)(Stat *stats[], const Entity *entity);

typedef struct Entity{
    char name[32];
    Stat stats[STAT_COUNT];
    Attribute attributes[ATR_COUNT];
    int gold;
    int kills;
    int level;
    int current_exp;
    int exp_to_next_level;
    Item inventory[INVENTORY_SIZE];
} Entity;

void take_damage(Entity *target, int damage, int attribute_id);
#endif