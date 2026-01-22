#include "entities.h"
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <stdbool.h>


void item_menu(Entity *p, Entity *target){
    if(is_inventory_empty(p)){
        printf("Your inventory is empty!\n");
        return;
    }

    printf("\nInventory:\n");
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(p->inventory[i].id != 0){
            printf("%d. %s\n", i + 1, p->inventory[i].name);
        }
    }
    printf("Choose an item to use (0 to cancel): ");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n');
    if(choice > 0 && choice <= INVENTORY_SIZE && p->inventory[choice - 1].id != 0){
        use_item(&p->inventory[choice - 1], p, target);
        // Remove item from inventory after use
        remove_item_at_index(p, choice);
    } else {
        printf("Cancelled item use.\n");
    }
}

void run_battle(Entity *p){
    // Create a simple monster
    // Todo: Clamp it within a level range.. after levels are added
    Entity monster = monster_pool[rand() % 3];

    printf("\nA wild %s appears!\n", monster.name);

    while(monster.current_hp > 0 && p->current_hp > 0){

        printf("\n%s: %d/%d HP | %s: %d HP", p->name, p->current_hp, p->max_hp, monster.name, monster.current_hp);
        printf("\n1. Attack\n2. UseItem\nChoice: ");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n');

        // Player attacks monster
        if(choice == 1)
            apply_damage(&monster, p);
        else if (choice == 2)
            item_menu(p, &monster);
        else
            printf("Invalid choice!\n");

        if(monster.current_hp <= 0){
            p->gold += monster.gold;
            p->kills += 1;
            printf("You earned %d gold!\n", monster.gold);
            break;
        } else {
            // Monster attacks player
            apply_damage(p, &monster);
        }
    }
}

