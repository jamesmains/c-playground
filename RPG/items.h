#ifndef ITEMS_H
#define ITEMS_H

struct Entity; 
typedef struct Entity Entity;

struct Item;
typedef struct Item Item;

typedef void (*ItemEffect)(Entity *user, Entity *target, const Item *item);

typedef struct Item{
    char name[30];
    int id;
    int cost;
    int power;
    ItemEffect effect;
} Item;

void use_item(const Item *item, Entity *user, Entity *target);

void effect_heal(Entity *user, Entity *target, const Item *item);

void effect_damage(Entity *user, Entity *target, const Item *item);
#endif