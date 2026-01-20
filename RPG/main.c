#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entities.h"

void run_battle(Entity *player);
void run_shop(Entity *player);

void await_user(){
    printf("Press Enter to continue...\n");
    fflush(stdin);
    getchar();
}

int main(){
    srand(time(NULL));

    // Create player entity
    Entity player = {"Hero", 30, 30, 5, 10, 0};

    printf("Welcome, %s! Your adventure awaits...\n", player.name);

    await_user();
    
    while(player.current_hp > 0){

        // Trigger a battle
        run_battle(&player);
        await_user();
        // Check if player is still alive
        if (player.current_hp <= 0){
            break;
        }
        

        // Random Event: 30% chance to enter shop
        if (rand() % 100 < 30){
            run_shop(&player);  
        }
    }

    printf("\n--- GAME OVER ---\n");
    printf("Monsters defeated: %d\n", player.kills);
    printf("Gold acquired: %d\n", player.gold);
    return 0;
}

