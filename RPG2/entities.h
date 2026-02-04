#ifndef ENTITIES_H
#define ENTITIES_H
#define INVENTORY_SIZE 20

// Include because full definition of Item is needed in Entity struct
#include "items.h"

// Forward declare because of circular dependency
struct Entity;
typedef struct Entity Entity;

struct Stat;
typedef struct Stat Stat;

typedef void (*EntityStats)(Stat *stats[], const Entity *entity);

typedef struct Entity{
    char name[32];
    EntityStats stats;
    int gold;
    int kills;
    Item inventory[INVENTORY_SIZE];
} Entity;
#endif