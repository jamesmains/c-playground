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

const Item all_items[] = {
    // Broadsword
    {
        .name = "Rusty Broadsword",
        .id = 1,
        .item_shop_cost = 10,
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
        .item_shop_cost = 25,
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
        .max_uses = 10,
        .uses_remaining = 10,
        .use_type = DURABLE,
    },
    {
        .name = "Fireball Scroll",
        .id = 3,
        .item_shop_cost = 15,
        .requirements = {
            { .stat_id = 1, .required_value = 5 }   // Intelligence >= 5
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 8, .dice_count = 3, .attribute_id = ATR_FIRE } // 3d8 fire damage
        },
        .dice_roll_count = 1,
        .effect = magic_damage_effect,
        .max_uses = 2,
        .uses_remaining = 2,
        .use_type = CASTS,
    },
    {
        .name = "Health Potion",
        .id = 4,
        .item_shop_cost = 10,
        .requirements = {
            { .stat_id = 3, .required_value = 5 }   // Endurance >= 5
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 6, .dice_count = 2 } // Heals for 2d6
        },
        .dice_roll_count = 1,
        .effect = physical_heal_effect,
        .max_uses = 1,
        .uses_remaining = 1,
        .use_type = USE,
    },
    {
        .name = "Greater Health Potion",
        .id = 5,
        .item_shop_cost = 25,
        .requirements = {
            { .stat_id = 3, .required_value = 10 }   // Endurance >= 10
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 8, .dice_count = 3 } // Heals for 3d8
        },
        .dice_roll_count = 1,
        .effect = physical_heal_effect,
        .max_uses = 1,
        .uses_remaining = 1,
        .use_type = USE
    },
    {
        .name = "Basic Poison Vial\t",
        .id = 6,
        .item_shop_cost = 15,
        .requirements = {
            { .stat_id = 2, .required_value = 5 }   // Intelligence >= 5
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 4, .dice_count = 4, .attribute_id = ATR_POISON } // Deals 4d4 poison damage
        },
        .dice_roll_count = 1,
        .effect = magic_damage_effect,
        .max_uses = 1,
        .uses_remaining = 1,
        .use_type = USE
    },
    {
        .name = "Greater Firebolt Scroll",
        .id = 7,
        .item_shop_cost = 20,
        .requirements = {
            { .stat_id = 2, .required_value = 7 }   // Intelligence >= 7
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 6, .dice_count = 4, .attribute_id = ATR_FIRE } // Deals 4d6 fire damage
        },
        .dice_roll_count = 1,
        .effect = magic_damage_effect,
        .max_uses = 5,
        .uses_remaining = 5,
        .use_type = CASTS
    },

    // Trunk-Like Arms (NO SHOP)
    {
        .name = "Trunk-Like Arms",
        .id = 8,
        .item_shop_cost = 999,
        .requirements = {
            { .stat_id = 0, .required_value = 5 } // Strength >= 5
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 12, .dice_count = 2 } // 2d12 damage
        },
        .dice_roll_count = 1,
        .effect = physical_damage_effect,
        .max_uses = 999,
        .uses_remaining = 999,
        .use_type = DURABLE,
    },
    // Spider Fangs (NO SHOP)
    {
        .name = "Spider Fangs",
        .id = 9,
        .item_shop_cost = 999,
        .requirements = {
            { .stat_id = 0, .required_value = 5 } // Strength >= 5
        },
        .requirement_count = 1,
        .rolls = {
            { .dice_sides = 4, .dice_count = 4 } // 4d4 damage
        },
        .dice_roll_count = 1,
        .effect = physical_damage_effect,
        .max_uses = 999,
        .uses_remaining = 999,
        .use_type = DURABLE,
    },
};
const Entity monster_pool[] = {
    // Goblin 0
    {
        .name = "Goblin",
        .gold = 5,
        .level = 1, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 6, .current_value = 5, .modifier = 0 },
            [STAT_DEX] = { .base_value = 14, .current_value = 14, .modifier = 0 },
            [STAT_INT] = { .base_value = 3, .current_value = 3, .modifier = 0 },
            [STAT_END] = { .base_value = 12, .current_value = 4, .modifier = 0 },
            [STAT_VIT] = { .base_value = 6, .current_value = 6, .modifier = 0 },
        },
        .attributes = {
            [ATR_FIRE] = { .resistance = 2, .weakness = 0 },
            [ATR_POISON] = { .resistance = 0, .weakness = 3 },
            [ATR_ICE] = { .resistance = 1, .weakness = 1 },
            [ATR_LIGHTNING] = { .resistance = 0, .weakness = 2 },
        },
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = all_items[0],
    },
    // Orc 1
    {
        .name = "Orc",
        .gold = 10,
        .level = 2, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 12, .current_value = 8, .modifier = 0 },
            [STAT_DEX] = { .base_value = 5, .current_value = 5, .modifier = 0 },
            [STAT_INT] = { .base_value = 4, .current_value = 4, .modifier = 0 },
            [STAT_END] = { .base_value = 14, .current_value = 6, .modifier = 0 },
            [STAT_VIT] = { .base_value = 12, .current_value = 12, .modifier = 0 },
        },
        .attributes = {
            [ATR_FIRE] = { .resistance = 1, .weakness = 1 },
            [ATR_POISON] = { .resistance = 0, .weakness = 2 },
            [ATR_ICE] = { .resistance = 2, .weakness = 0 },
            [ATR_LIGHTNING] = { .resistance = 0, .weakness = 3 },
        },
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = all_items[1],
    },
    // Troll 2
    {
        .name = "Troll",
        .gold = 40,
        .level = 5, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 22, .current_value = 12, .modifier = 0 },
            [STAT_DEX] = { .base_value = 10, .current_value = 4, .modifier = 0 },
            [STAT_INT] = { .base_value = 3, .current_value = 3, .modifier = 0 },
            [STAT_END] = { .base_value = 22, .current_value = 8, .modifier = 0 },
            [STAT_VIT] = { .base_value = 35, .current_value = 20, .modifier = 0 },
        },
        // Hella resistant but weak to fire.
        .attributes = {
            [ATR_FIRE] = { .resistance = 0, .weakness = 5 },
            [ATR_POISON] = { .resistance = 10, .weakness = 0 },
            [ATR_ICE] = { .resistance = 10, .weakness = 1 },
            [ATR_LIGHTNING] = { .resistance = 10, .weakness = 2 },
        },
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = all_items[7],
    },
    // Giant Spider 3
    {
        .name = "Giant Spider",
        .gold = 15,
        .level = 2, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 8, .current_value = 8, .modifier = 0 },
            [STAT_DEX] = { .base_value = 12, .current_value = 12, .modifier = 0 },
            [STAT_INT] = { .base_value = 2, .current_value = 2, .modifier = 0 },
            [STAT_END] = { .base_value = 10, .current_value = 5, .modifier = 0 },
            [STAT_VIT] = { .base_value = 10, .current_value = 10, .modifier = 0 },
        },
        // Resistant to physical but weak to poison.
        .attributes = {
            [ATR_FIRE] = { .resistance = 1, .weakness = 1 },
            [ATR_POISON] = { .resistance = 0, .weakness = 4 },
            [ATR_ICE] = { .resistance = 1, .weakness = 0 },
            [ATR_LIGHTNING] = { .resistance = 1, .weakness = 2 },
        },
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = all_items[8],
    },
    // Skeleton Warrior 4
    {
        .name = "Skeleton Warrior",
        .gold = 12,
        .level = 2, // May need to adjust this based on room or player level?
        .stats = {
            [STAT_STR] = { .base_value = 10, .current_value = 10, .modifier = 0 },
            [STAT_DEX] = { .base_value = 10, .current_value = 10, .modifier = 0 },
            [STAT_INT] = { .base_value = 2, .current_value = 2, .modifier = 0 },
            [STAT_END] = { .base_value = 12, .current_value = 6, .modifier = 0 },
            [STAT_VIT] = { .base_value = 8, .current_value = 8, .modifier = 0 },
        },
        // Resistant to physical but weak to blunt and fire.
        .attributes = {
            [ATR_FIRE] = { .resistance = 0, .weakness = 3 },
            [ATR_POISON] = { .resistance = 1, .weakness = 0 },
            [ATR_ICE] = { .resistance = 1, .weakness = 0 },
            [ATR_LIGHTNING] = { .resistance = 1, .weakness = 1 },
        },
        .combat_logic = default_ai_combat_logic,
        .inventory[0] = all_items[0],
    }
};

const Shop shops[] = {
    {
        .name = "Bob's Hero Emporium",
        .description = "A customer! Please, look around!",
        .shop_items = { all_items[0], all_items[2], all_items[3] },
        .item_count = 3,
    },
    {
        .name = "Wanting Wall",
        .description = "Give... Gold... Get... Items...",
        .shop_items = { all_items[4], all_items[5], all_items[6] },
        .item_count = 3,
    }
};

const Map maps[] = {
    // Map 0 10x17
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
        .enemy_pool_count = 1,
        .doors = {
            { .x = 16, .y = 4, .leads_to_map_id = 1, .dest_x = 1, .dest_y = 7 }, // To Hall
        },
        .door_count = 1,
        .shop_id = -1, // No shop on this map
    },
    // Map 1 10x35
    {
        .map_name = "Hall of Heroes",
        .data = (const char*[]){
            "+===========|     |======|         ",
            "|           |     |      |         ",
            "|           |===+ +=|  |=+         ",
            "|     $         |   |  |           ",
            "|  |======|     |====  ============",
            "|                                  ",
            "|                                  ",
            "|               |=====|   |========",
            "|               |     |   |        ",
            "+===============+     +===+        ",
        },
        .height = 10,
        .width = 35,
        .enemy_pool = {
            monster_pool[0],
            monster_pool[1],
        },
        .enemy_pool_count = 2,
        .doors = {
            { .x = 0, .y = 7, .leads_to_map_id = 0, .dest_x = 15, .dest_y = 4 }, // Return To Gallery
            { .x = 21, .y = 0, .leads_to_map_id = 2, .dest_x = 8, .dest_y = 8 }, // To Chamber
            { .x = 24, .y = 8, .leads_to_map_id = 3, .dest_x = 7, .dest_y = 3 }, // To Well
        },
        .door_count = 3,
        .shop_id = 0, // Bob's Emporium is on this map
    },
    // Map 2 10x17
    {
        .map_name = "Chamber of Big Bad",
        .data = (const char*[]){
            "+===============+",
            "|               |",
            "|       M       |",
            "|               |",
            "|               |",
            "|               |",
            "|               |",
            "|               |",
            "|               |",
            "+===============+",
        },
        .height = 10,
        .width = 17,
        .enemy_pool = {
            monster_pool[2],
        },
        .enemy_pool_count = 1,
        .doors = {
            { .x = 8, .y = 9, .leads_to_map_id = 1, .dest_x = 21, .dest_y = 1 }, // Return to Hall
        },
        .door_count = 1,
        .shop_id = -1, // No shop on this map
    },
    // Map 3 6x13
    {
        .map_name = "Empty Well Bed",
        .data = (const char*[]){
            "+===========+",
            "| M         |",
            "|           |",
            "|           |",
            "|           |",
            "+===========+",
        },
        .height = 6,
        .width = 13,
        .enemy_pool = {
            monster_pool[3],
        },
        .enemy_pool_count = 1,
        .doors = {
            { .x = 12, .y = 2, .leads_to_map_id = 4, .dest_x = 1, .dest_y = 1 }, // To Water Way
        },
        .door_count = 1,
        .shop_id = -1, // No shop on this map
    },
    // Map 4 10x35
    {
        .map_name = "Wasting Water Way",
        .data = (const char*[]){
            "|=================================|",
            "|     M                   M       |",
            "|=| |===|=====|=====|=======|   |=|",
            "  | | M | $   | M   |  | M  |   |  ",
            "  |     |= =| +=| |=+  =====| ==|=+",
            "  | |===|   |===| |====           |",
            "  |                          M    |",
            "  +===|====| |==|=====|   |=======+",
            "      | M    |  |         |        ",
            "      +======+  +=========+        ",
        },
        .height = 10,
        .width = 35,
        .enemy_pool = {
            monster_pool[3],
            monster_pool[4],
        },
        .enemy_pool_count = 2,
        .doors = {
            {.x = 0, .y = 1, .leads_to_map_id = 3, .dest_x = 11, .dest_y = 2}, // Return to Well
            { .x = 19, .y = 8, .leads_to_map_id = 0, .dest_x = 9, .dest_y = 8 }, // To Gallery
        },
        .door_count = 2,
        .shop_id = 1, // No shop on this map
    },
};