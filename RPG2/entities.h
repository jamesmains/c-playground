#ifndef ENTITIES_H
#define ENTITIES_H
#define INVENTORY_SIZE 20
#define NEW_LEVEL_EXP_INCREMENT 50

// Include because full definition of Item is needed in Entity struct
#include "items.h"
#include "stats.h"

// Forward declare because of circular dependency
struct Entity;
typedef struct Entity Entity;

//typedef void (*EntityStats)(Stat *stats[], const Entity *entity);
typedef void (*EntityCombatLogic)(Entity *user, Entity *target, const Item *item);


typedef struct Entity{
    char name[32];
    Stat stats[STAT_COUNT];
    Attribute attributes[ATR_COUNT];
    int gold;
    int kills;
    int level;
    int x;
    int y;
    int current_exp;
    int exp_to_next_level;
    Item inventory[INVENTORY_SIZE];
    EntityCombatLogic combat_logic;
} Entity;
void win_match(Entity* player, Entity* opponent); // Using Player and Opponent terminology for clarity as only the player should hit this, but they are both just Entities
void take_damage(Entity *target, int damage, int attribute_id);
void player_combat_logic(Entity *user, Entity *target, const Item *item);
void default_ai_combat_logic(Entity *user, Entity *target, const Item *item);
void remove_item_at_index(Entity *p, int index);
void add_item(Entity *p, Item item);
int get_stat_modifier(const Entity *entity, StatType stat_id, int min);
#endif