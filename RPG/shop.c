#include "entities.h"
#include <stdio.h>
#include "database.h"

void run_shop(Entity *p){
    printf("\nWelcome to the shop, %s! You have %d gold.\n", p->name, p->gold);
    printf("Available items:\n");
    for(int i = 0; i < 2; i++){
        printf("%d. %s - Cost: %d gold\n", i + 1, shop_items[i].name, shop_items[i].cost);
    }
    printf("Choose an item to buy (0 to exit): ");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n');
    if(choice > 0 && choice <= 2){
        Item selectedItem = shop_items[choice - 1];
        if(p->gold >= selectedItem.cost){
            p->gold -= selectedItem.cost;
            add_item(p, selectedItem);
            printf("You bought a %s!\n", selectedItem.name);
        } else {
            printf("You don't have enough gold!\n");
        }
    } else {
        printf("Exiting shop.\n");
    }
    return;
}