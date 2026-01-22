#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "player.h"

void set_conio_terminal_mode(){
    struct termios new_termios;

    tcgetattr(0, &new_termios);
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}


#define BOARD_WIDTH 15
#define BOARD_HEIGHT 6
void draw_board(Player *player){
    printf("\033[H\033[J"); // Clear screen
    for(int y = 0; y < BOARD_HEIGHT; y++){
        for(int x = 0; x < BOARD_WIDTH; x++){
            if(x == player->x && y == player->y)
                printf("O");
            else
                printf(".");
        }
        printf("\n");
    }
    
}

void get_player_input(Player *player){
    char input = getchar();
    switch(input){
        case 'W':
        case 'w':
            player->directionX = 0;
            player->directionY = -1;
            break;
        case 'A':
        case 'a':
            player->directionX = -1;
            player->directionY = 0;
            break;
        case 'S':
        case 's':
            player->directionX = 0;
            player->directionY = 1;
            break;
        case 'D':
        case 'd':
            player->directionX = 1;
            player->directionY = 0;
            break;
        case 'Q':
        case 'q':
            player->alive = 0;
            break;
    }
    player->x += player->directionX;
    player->y += player->directionY;

    // Keep player within bounds
    if(player->x < 0) player->x = 0;
    if(player->x >= BOARD_WIDTH) player->x = BOARD_WIDTH - 1;
    if(player->y < 0) player->y = 0;
    if(player->y >= BOARD_HEIGHT) player->y = BOARD_HEIGHT - 1;
}

int main(){
    set_conio_terminal_mode();

    Player player = {
        .alive = 1,
        .x = BOARD_WIDTH / 2,
        .y = BOARD_HEIGHT / 2,
        .length = 1,
        .directionX = 0,
        .directionY = 0
    };
    while(player.alive){
        if(kbhit())
            {get_player_input(&player);}
        draw_board(&player);
        char input = getchar();
        printf("Input: %c\n", input);
        printf("Player Position: (%d, %d)\n", player.x, player.y);
        usleep(100000);
    }
    return 0;
}