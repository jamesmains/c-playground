#include "entities.h"
#include "items.h"

const Entity monster_pool[] = {
    {.name = "Goblin", .max_hp = 20, .current_hp = 20, .max_mana = 0, .current_mana = 0, .attack = 3, .gold = 5, .kills = 0},
    {.name = "Orc", .max_hp = 30, .current_hp = 30, .max_mana = 0, .current_mana = 0, .attack = 5, .gold = 10, .kills = 0},
    {.name = "Troll", .max_hp = 50, .current_hp = 50, .max_mana = 0, .current_mana = 0, .attack = 8, .gold = 20, .kills = 0},
};

const Item shop_items[] = {
    {.name = "Weak Health Potion", .id = 1, .cost = 5, .power = 10, .effect = effect_heal},
    {.name = "Strong Health Potion", .id = 2, .cost = 15, .power = 25, .effect = effect_heal},
    {.name = "Fireball Scroll", .id = 3, .cost = 10, .power = 15, .effect = effect_damage},
};