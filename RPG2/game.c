#include "game.h"
#include "database.h"
#include <stdio.h>
#include <termio.h>
#include <unistd.h>

void await_user()
{
    printf("Press Enter to continue...\n");
    fflush(stdin);
    getchar();
}

char get_input() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar(); // Grabs the key immediately
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore settings
    return ch;
}

void game_loop(GameContext *ctx)
{
    if (ctx->state == STATE_EXPLORE)
    {
        // Todo: get player input
        char c = get_input();
        int move_dir_y = 0;

        if(c == 'w')
            move_dir_y = -1;
        else if (c == 's')
            move_dir_y = 1;

        int move_dir_x = 0;

        if(c == 'd')
            move_dir_x = 1;
        else if (c == 'a')
            move_dir_x = -1;

        move_entity(ctx->player,ctx->current_map,move_dir_x, move_dir_y);
        // Todo: move enemies after input (if any)
        draw_world(ctx->current_map, ctx->player->x, ctx->player->y);
        printf("%d, player x: %d, player y: %d", ctx->state, ctx->player->x, ctx->player->y);
        //await_user();
    }
    // Item i = shop_items[2];
    //Entity e = monster_pool[0];
    // printf("\nItem: %s\n", i.name);
    // printf("Monster: %s\n", e.name);
    // if (i.effect != NULL)
    // {
    //     i.effect(ctx->player, &e, &i);
    // }
    
}