#include "entities.h"
#include <stdio.h>

void run_battle(Entity *p){
    // Create a simple monster
    Entity monster = {"Goblin", 10 + (p->kills * 2), 10, 3 + p->kills, 5, 0};

    printf("\nA wild %s appears!\n", monster.name);

    while(monster.current_hp > 0 && p->current_hp > 0){
        printf("\n%s: %d/%d HP | %s: %d HP", p->name, p->current_hp, p->max_hp, monster.name, monster.current_hp);
        printf("\n1. Attack\nChoice: ");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n');
        // Player attacks monster
        monster.current_hp -= p->attack;
        printf("\nYou dealt %d damage to the %s!\n", p->attack, monster.name);

        if(monster.current_hp <= 0){
            printf("You defeated the %s!\n", monster.name);
            p->gold += monster.gold;
            p->kills += 1;
            printf("You earned %d gold!\n", monster.gold);
            break;
        } else {
            // Monster attacks player
            p->current_hp -= monster.attack;
            printf("The %s dealt %d damage to you!\n", monster.name, monster.attack); 
        }
    }

}