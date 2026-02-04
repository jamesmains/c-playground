#include "entities.h"
#include "stats.h"
#include <stdio.h>

void take_damage(Entity *target, int damage, int attribute_id) {
    // Apply attribute resistance/weakness
    int resistance = target->attributes[attribute_id].resistance;
    int weakness = target->attributes[attribute_id].weakness;
    
    damage -= resistance;
    damage += weakness;
    
    if (damage < 1) {
        damage = 1; // Ensure at least 1 damage is dealt
    }

    target->stats[HEALTH_STAT_ID].current_value -= damage;
    if(target->stats[HEALTH_STAT_ID].current_value < 0)
        target->stats[HEALTH_STAT_ID].current_value = 0;
    printf("Result: %s took %d damage! (%d HP remaining)\n", 
            target->name, damage, target->stats[HEALTH_STAT_ID].current_value);
}