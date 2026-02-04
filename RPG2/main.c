#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entities.h"
#include "items.h"
#include "database.h"
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif
// ▄   ▜             ▐▘  ▄▖       ▘
// ▌▌█▌▐ ▌▌█▌▛▘▛▘  ▛▌▜▘  ▐ █▌▛▘▛▛▌▌▛▌▀▌
// ▙▘▙▖▐▖▚▘▙▖▌ ▄▌  ▙▌▐   ▐ ▙▖▌ ▌▌▌▌▌▌█▌
//
//
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
        SLEEP_MS(500);
        printf("%s\n", title[i]);
    }
    Item i = shop_items[1];
    Entity e = monster_pool[0];
    printf("\nItem: %s\n", i.name);
    printf("Monster: %s\n", e.name);
    i.effect(&e, &e, &i);
    return 0;
}