#include "entities.h"
#include <stdio.h>

void use_item(const Item *item, Entity *user, Entity *target) {
    if(item != NULL && item->effect != NULL) {
        item->effect(user, target, item);
    } else {
        printf("No held item!\n");
    }
}

void effect_heal(Entity *user, Entity *target, const Item *item) {
    user->current_hp += item->power;
    if (user->current_hp > user->max_hp) user->current_hp = user->max_hp;
    printf("%s used a potion and healed for %d!\n", user->name, item->power);
}

void effect_damage(Entity *user, Entity *target, const Item *item) {
    if(user->current_mana < item->cost){
        printf("Not enough mana to use %s!\n", item->name);
        return;
    }
    target->current_hp -= item->power;
    user->current_mana -= item->cost;
    printf("%s dealt %d damage to %s!\n", user->name, item->power, target->name);
}