#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entities.h"
#include <string.h>
#include "database.h"

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
    //Entity player = {"Hero", 30, 30,0,0, 5, 10, 0};

    printf("What is your name?\n");
    char choice[30];
    scanf("%29s", choice);
    Entity player = {
        .max_hp = 30,
        .current_hp = 30,
        .max_mana = 100,
        .current_mana = 100,
        .attack = 5,
        .gold = 10,
        .kills = 0,
        .inventory[0] = shop_items[0],
        .inventory[1] = shop_items[0],
        .inventory[2] = shop_items[2]
    };
    strncpy(player.name, choice, sizeof(player.name) - 1);
    while (getchar() != '\n');
    printf("Welcome, %s! Your adventure awaits...\n", player.name);

    await_user();

    while (player.current_hp > 0)
    {

        // Trigger a battle
        run_battle(&player);
        await_user();
        // Check if player is still alive
        if (player.current_hp <= 0)
        {
            break;
        }

        // Go to shop after every battle
        run_shop(&player);

        // Random Event: 30% chance to enter shop
        // if (rand() % 100 < 30)
        // {
        //     run_shop(&player);
        // }
    }

    printf("\n--- GAME OVER ---\n");
    printf("Monsters defeated: %d\n", player.kills);
    printf("Gold acquired: %d\n", player.gold);
    return 0;
}

