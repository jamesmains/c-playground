#include "items.h"
#include "stats.h"
#include "entities.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool requirement_check(Entity *user, Stat *requirements[], const Item *item) {
    for (int i = 0; i < item->requirement_count; i++) {
        Requirement req = item->requirements[i];
        Stat *stat = requirements[req.stat_id];
        if (stat->current_value < req.required_value) {
            printf("%s does not meet the requirement for %s.\n", user->name, item->name);
            return false;
        }
    }
    printf("%s meets all requirements for %s.\n", user->name, item->name);
    return true;
}

int dice_roll(DiceRoll *roll, const Item *item) {
    int total = 0;
    for (int i = 0; i < roll->dice_count; i++) {
        total += (rand() % roll->dice_sides) + 1;
    }
    return total;
}

int roll_all_dice(const Item *item) {
    int total = 0;
    for (int j = 0; j < item->dice_roll_count; j++) {
        int roll_sum = 0;
        DiceRoll current_roll = item->rolls[j];

        printf("  Rolling %dd%d: ", current_roll.dice_count, current_roll.dice_sides);

        for (int d = 0; d < current_roll.dice_count; d++) {
            // We use roll but for 1 die at a time to see them
            DiceRoll single = {.dice_sides = current_roll.dice_sides, .dice_count = 1};
            int val = dice_roll(&single, item);
            
            printf("[%d] ", val);
            roll_sum += val;
        }
        total += roll_sum;
        printf("| Subtotal: %d\n", roll_sum);
    }
    return total;
}

void physical_damage_effect(Entity *user, Entity *target, const Item *item) {
    int total_damage = 0;
    printf("\033[H\033[J");
    printf("\n%s attacks %s with %s!\n", user->name, target->name, item->name);

    // Get base total damage from dice rolls
    total_damage += roll_all_dice(item);

    // Allow str mod to go negative because maybe the creature is weak but still needs to attack.
    total_damage += get_stat_modifier(user, STAT_STR, MINIMUM_STAT_MODIFIER);

    // Now, actually modify the target
    take_damage(target, total_damage, item->rolls[0].attribute_id);
}

void magic_damage_effect(Entity *user, Entity *target, const Item *item) {
    int total_damage = 0;
    printf("\033[H\033[J");
    printf("\n%s casts %s on %s!\n", user->name, item->name, target->name);

    // Get base total damage from dice rolls
    total_damage += roll_all_dice(item);

    // Allow str mod to go negative because maybe the creature is weak but still needs to attack.
    total_damage += get_stat_modifier(user, STAT_INT, MINIMUM_STAT_MODIFIER);
    
    // Now, actually modify the target
    take_damage(target, total_damage, item->rolls[0].attribute_id);
}

void physical_heal_effect(Entity *user, Entity *target, const Item *item){
    int total_healing = 0;
    printf("\033[H\033[J");
    printf("\n%s uses %s!\n", user->name, item->name);
    // Get base total healing from dice rolls
    total_healing += roll_all_dice(item);
    heal_damage(user, total_healing);
}