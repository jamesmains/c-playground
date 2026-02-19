#include "game.h"
#include "database.h"
#include "explore.h"
#include "combat.h"
#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#include <string.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void await_user()
{
    printf("Press Enter to continue...\n");
    fflush(stdin);
    getchar();
}

char get_input()
{
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
        handle_explore(ctx);
    }
    else if (ctx->state == STATE_COMBAT)
    {
        handle_combat(ctx);
    }
    else if (ctx->state == STATE_SHOP)
    {
        handle_shop(ctx);
    }
}