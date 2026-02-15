#include "entities.h"
#include "items.h"
#include "stats.h"
#include "world.h"

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

const Item shop_items[] = {
    // Broadsword
    {
        .name = "Broadsword",
        .id = 1,
        .requirements = {
            { .stat_id = 0, .required_value = 5 } // Strength >= 5
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 6, .dice_count = 2 } // 2d6 damage
        },
        .dice_roll_count = 1,
        .effect = physical_damage_effect,
        .max_uses = 75,
        .uses_remaining = 75,
        .use_type = DURABLE,
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
        .rolls = {
            { .dice_sides = 6, .dice_count = 1, .attribute_id = ATR_FIRE }, // 1d6 fire damage
            { .dice_sides = 4, .dice_count = 2, .attribute_id = ATR_PHYSICAL }  // 2d4 physical damage
        },
        .dice_roll_count = 2,
        .effect = physical_damage_effect,
        .max_uses = 2,
        .uses_remaining = 2,
        .use_type = DURABLE,
    },
    // Test No Effect Item
    {
        .name = "Dull Coin",
        .id = 3,
        .requirements = {
            { .stat_id = 0, .required_value = 0 }
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 6, .dice_count = 1, .attribute_id = ATR_PHYSICAL }
        },
        .dice_roll_count = 1,
    }
};
const Entity monster_pool[] = {
    {
        .name = "Goblin",
        .gold = 5,
        .level = 1, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 5, .current_value = 5, .modifier = 0 },
            [STAT_DEX] = { .base_value = 14, .current_value = 14, .modifier = 0 },
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
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = shop_items[0],
    },
    {
        .name = "Orc",
        .gold = 10,
        .level = 2, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 8, .current_value = 8, .modifier = 0 },
            [STAT_DEX] = { .base_value = 5, .current_value = 5, .modifier = 0 },
            [STAT_INT] = { .base_value = 4, .current_value = 4, .modifier = 0 },
            [STAT_END] = { .base_value = 6, .current_value = 6, .modifier = 0 },
            [STAT_VIT] = { .base_value = 12, .current_value = 12, .modifier = 0 },
        },
        .attributes = {
            [ATR_FIRE] = { .resistance = 1, .weakness = 1 },
            [ATR_POISON] = { .resistance = 0, .weakness = 2 },
            [ATR_ICE] = { .resistance = 2, .weakness = 0 },
            [ATR_LIGHTNING] = { .resistance = 0, .weakness = 3 },
        },
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = shop_items[1],
    }
};

const Map maps[] = {
    {
        .map_name = "Gallery of Termina",
        .data = (const char*[]){
            "=================",
            "|               |",
            "|       M       |",
            "|               |",
            "|  |======|     |",
            "|               |",
            "|               |",
            "| M             |",
            "|            M  |",
            "=================",
        },
        .height = 10,
        .width = 17,
        .enemy_pool = {
            monster_pool[0],
        },
        .doors = {
            { .x = 8, .y = 0, .leads_to_map_id = 1, .dest_x = 1, .dest_y = 1 },
        }
    },
    {
        .map_name = "Hall of Heroes",
        .data = (const char*[]){
            "============|     |======|         ",
            "|           |     |      |         ",
            "|           |===  ==|  |==         ",
            "|               |   |  |           ",
            "|  |======|     |====  ============",
            "|                                  ",
            "|                                  ",
            "|               |==================",
            "|               |                  ",
            "=================                  ",
        },
        .height = 10,
        .width = 35,
        .enemy_pool = {
            monster_pool[0],
        },
        .doors = {
            { .x = 8, .y = 9, .leads_to_map_id = 0, .dest_x = 8, .dest_y = 1 },
        }
    }
};