#ifndef ENTITIES_H
#define ENTITIES_H
#define INVENTORY_SIZE 10
#include "items.h"
#include <stdbool.h>
typedef struct Entity{
    char name[30];
    int max_hp;
    int current_hp;
    int max_mana;
    int current_mana;
    int attack;
    int gold;
    int kills;
    Item inventory[INVENTORY_SIZE];
} Entity;
void apply_damage(Entity *target, Entity *source);
bool is_inventory_empty(Entity *player);
void remove_item_at_index(Entity *p, int index);
void add_item(Entity *p, Item item);
#endif