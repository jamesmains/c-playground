#include "entities.h"
#include "items.h"
#include "stats.h"

const char *attribute_names[ATR_COUNT][1] = {
    [ATR_FIRE] = {
        "Fire",
    },
    [ATR_POISON] = {
        "Poison",
    },
    [ATR_ICE] = {
        "Ice",
    },
    [ATR_LIGHTNING] = {
        "Lightning",
    }
};

const Entity monster_pool[] = {
    {
        .name = "Goblin",
        .gold = 5,
        .kills = 0,
        .stats = {
            [STAT_STR] = { .base_value = 5, .current_value = 5, .modifier = 0 },
            [STAT_DEX] = { .base_value = 7, .current_value = 7, .modifier = 0 },
            [STAT_INT] = { .base_value = 3, .current_value = 3, .modifier = 0 },
            [STAT_END] = { .base_value = 4, .current_value = 4, .modifier = 0 },
            [STAT_VIT] = { .base_value = 6, .current_value = 6, .modifier = 0 },
        },
        .attributes = {
            [ATR_FIRE] = { .resistance = 2, .weakness = 0 },
            [ATR_POISON] = { .resistance = 0, .weakness = 3 },
            [ATR_ICE] = { .resistance = 1, .weakness = 1 },
            [ATR_LIGHTNING] = { .resistance = 0, .weakness = 2 },
        },
    },
};

const Item shop_items[] = {
    // Broadsword
    {
        .name = "Broadsword",
        .id = 1,
        .requirements = {
            { .stat_id = 0, .required_value = 5 } // Strength >= 5
        },
        .requirement_count = 1,
        .stat_check = default_requirement_check,
        .dice_roll_function = default_dice_roll,
        .rolls = {
            { .dice_sides = 6, .dice_count = 2 } // 2d6 damage
        },
        .dice_roll_count = 1,
        .effect = physical_damage_effect,
    },
    // Flaming Sword
    {
        .name = "Flaming Sword",
        .id = 2,
        .requirements = {
            { .stat_id = 0, .required_value = 10 }, // Strength >= 10
            { .stat_id = 1, .required_value = 5 }   // Intelligence >= 5
        },
        .requirement_count = 2,
        .stat_check = default_requirement_check,
        .dice_roll_function = default_dice_roll,
        .rolls = {
            { .dice_sides = 6, .dice_count = 1, .attribute_id = ATR_FIRE }, // 1d6 fire damage
            { .dice_sides = 4, .dice_count = 2, .attribute_id = ATR_PHYSICAL }  // 2d4 physical damage
        },
        .dice_roll_count = 2,
        .effect = physical_damage_effect,
    }
};
