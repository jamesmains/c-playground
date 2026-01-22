#include "entities.h"
#include <stdio.h>

void apply_damage(Entity *target, Entity *source){
    target->current_hp -= source->attack;
    printf("%s dealt %d damage to %s!\n", source->name, source->attack, target->name);
    if (target->current_hp < 0) {
        target->current_hp = 0;
        printf("%s has been defeated!\n", target->name);
    }
}

bool is_inventory_empty(Entity *player) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        // If we find ANY slot that isn't empty, the inventory isn't empty
        if (player->inventory[i].id != 0) { 
            return false; 
        }
    }
    // If the loop finishes, it means every slot was empty
    return true;
}

void remove_item_at_index(Entity *p, int index){
    printf("Removing item at index %d from %s's inventory.\n", index-1, p->name);
    if(index < 0 || index >= INVENTORY_SIZE){
        printf("Invalid inventory index!\n");
        return;
    }
    p->inventory[index - 1].id = 0; // Reset the item slot to an empty item
    for (int i = index - 1; i < INVENTORY_SIZE - 1; i++)
    {
        p->inventory[i] = p->inventory[i + 1];
    }
    p->inventory[INVENTORY_SIZE - 1].id = 0; // Clear the last slot
}

void add_item(Entity *p, Item item){
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(p->inventory[i].id == 0){
            p->inventory[i] = item;
            printf("Added %s to %s's inventory.\n", item.name, p->name);
            return;
        }
    }
    printf("%s's inventory is full! Cannot add %s.\n", p->name, item.name);
}