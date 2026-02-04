#include "entities.h"
#include "items.h"

const Entity monster_pool[] = {
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
            { .dice_sides = 6, .dice_count = 3 }, // 3d6 damage
            { .dice_sides = 4, .dice_count = 2 }  // 2d4 fire damage
        },
        .dice_roll_count = 2,
    }
};
