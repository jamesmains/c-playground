#include "items.h"
#include "stats.h"
#include "entities.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool default_requirement_check(Entity *user, Stat *requirements[], const Item *item) {
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

int default_dice_roll(DiceRoll *roll, const Item *item) {
    int total = 0;
    for (int i = 0; i < roll->dice_count; i++) {
        total += (rand() % roll->dice_sides) + 1;
    }
    return total;
}