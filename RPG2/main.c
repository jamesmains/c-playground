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
//▄   ▜             ▐▘  ▄▖       ▘    
//▌▌█▌▐ ▌▌█▌▛▘▛▘  ▛▌▜▘  ▐ █▌▛▘▛▛▌▌▛▌▀▌
//▙▘▙▖▐▖▚▘▙▖▌ ▄▌  ▙▌▐   ▐ ▙▖▌ ▌▌▌▌▌▌█▌
//                                    
//
const char *title[] = {
    "▄   ▜             ▐▘  ▄▖       ▘    ",
    "▌▌█▌▐ ▌▌█▌▛▘▛▘  ▛▌▜▘  ▐ █▌▛▘▛▛▌▌▛▌▀▌",
    "▙▘▙▖▐▖▚▘▙▖▌ ▄▌  ▙▌▐   ▐ ▙▖▌ ▌▌▌▌▌▌█▌"
};
int main(){
    srand(time(NULL));
    printf("\033[H\033[J");
    for(int i = 0; i < 3; i++){
        SLEEP_MS(500);
        printf("%s\n", title[i]);
    }
    Item i = shop_items[1];
    printf("Item: %s, ID: %d\n", i.name, i.id);
    for(int j = 0; j < i.dice_roll_count; j++) {
    printf("Roll #%d results: ", j + 1);
    int total_for_this_roll = 0;

    for(int d = 0; d < i.rolls[j].dice_count; d++) {
        // Create a temporary "single" die roll to pass to your function
        DiceRoll single_die = { .dice_sides = i.rolls[j].dice_sides, .dice_count = 1 };
        int val = i.dice_roll_function(&single_die, &i);
        
        printf("[%d] ", val);
        total_for_this_roll += val;
    }
    printf("| Total: %d\n", total_for_this_roll);
}
    
    return 0;
}