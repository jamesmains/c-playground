#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entities.h"
#include "items.h"
#include "database.h"
#include "world.h"
#include "game.h"
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#include <string.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

const char *title[] = {
    "▄   ▜             ▐▘  ▄▖       ▘    ",
    "▌▌█▌▐ ▌▌█▌▛▘▛▘  ▛▌▜▘  ▐ █▌▛▘▛▛▌▌▛▌▀▌",
    "▙▘▙▖▐▖▚▘▙▖▌ ▄▌  ▙▌▐   ▐ ▙▖▌ ▌▌▌▌▌▌█▌"};


int main()
{
    srand(time(NULL));
    printf("\033[H\033[J");
    for (int i = 0; i < 3; i++)
    {
        // Todo: uncomment for full effect
        //SLEEP_MS(500);
        printf("%s\n", title[i]);
    }
    // Todo: uncomment for full effect
    //SLEEP_MS(500);
    printf("What is your name?\n");
    char choice[32];
    scanf("%31s", choice);
    Entity player = {
        .attributes = {
            [ATR_FIRE] = {.resistance = 0, .weakness = 0},
            [ATR_POISON] = {.resistance = 0, .weakness = 3},
            [ATR_ICE] = {.resistance = 0, .weakness = 0},
            [ATR_LIGHTNING] = {.resistance = 0, .weakness = 0},
        },
        .stats = {
            [STAT_STR] = {.base_value = 5, .current_value = 5, .modifier = 0},
            [STAT_DEX] = {.base_value = 5, .current_value = 5, .modifier = 0},
            [STAT_INT] = {.base_value = 5, .current_value = 5, .modifier = 0},
            [STAT_END] = {.base_value = 5, .current_value = 5, .modifier = 0},
            [STAT_VIT] = {.base_value = 5, .current_value = 5, .modifier = 0},
        },
        .gold = 10,
        .kills = 0,
        .level = 1,
        .x = 4,
        .y = 4,
        .current_exp = 0,
        .exp_to_next_level = 100,
        .inventory[0] = shop_items[0],
    };
    strncpy(player.name, choice, sizeof(player.name) - 1);
    GameContext ctx = {
        .player = &player,
        .state = STATE_EXPLORE,
    };
    set_map(&ctx, &map_1);
    SLEEP_MS(500);
    printf("Welcome, %s! Your adventure awaits...\n", player.name);
    await_user();

    // Core check, make sure player is still alive
    while (player.stats[STAT_VIT].current_value > 0)
    {
        game_loop(&ctx);
    }

    return 0;
}