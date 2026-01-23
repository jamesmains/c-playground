#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "player.h"
#include "fruit.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 7

#define GAME_SPEED 350000 // 0.35 seconds

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

void draw_board(Player *player, Fruit *fruit, Player *children, int childCount){
    printf("\033[H\033[J"); // Clear screen
    int prevX = player->x;
    int prevY = player->y;

    player->x += player->directionX;
    player->y += player->directionY;
    
    for (int i = 0; i < childCount; i++) {
        if (player->x == children[i].x && player->y == children[i].y) {
            player->alive = 0;
            break;
        }
    }

    // Keep player within bounds
    if(player->x < 0) player->x = 0;
    if(player->x >= BOARD_WIDTH) player->x = BOARD_WIDTH - 1;
    if(player->y < 0) player->y = 0;
    if(player->y >= BOARD_HEIGHT) player->y = BOARD_HEIGHT - 1;
    
    for (int i = 0; i < childCount; i++) {
        // Store current child position
        int tempX = children[i].x;
        int tempY = children[i].y;

        // Move current child to the previous position of the one in front
        children[i].x = prevX;
        children[i].y = prevY;

        // Update prevX/Y so the NEXT child moves to THIS child's old spot
        prevX = tempX;
        prevY = tempY;
    }
    
    for(int y = 0; y < BOARD_HEIGHT; y++){
        for(int x = 0; x < BOARD_WIDTH; x++){
            int childAtPos = 0;
            for (int c = 0; c < childCount; c++)
            {
                if (x == children[c].x && y == children[c].y)
                {
                    printf("o");
                    childAtPos = 1;
                    break;
                }
            }
            if (childAtPos == 1)
                continue;
            if(x == player->x && y == player->y)
                printf("O");
            else if(x == fruit->x && y == fruit->y)
                printf("F");
            else
                printf(".");
        }

        printf("\n");
    }

    // printf("[DEBUG] Player Direction: (%d, %d)\n", player->directionX, player->directionY);
    // printf("[DEBUG] Child Count: %d\n", childCount);
    // printf("[DEBUG] Overlapping Player and Child: %d\n", overlappingPlayer);
    printf("Score: %d\n", player->score);
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
    
}

int check_fruit_collision(Player *player, Fruit *fruit){
    if(player->x == fruit->x && player->y == fruit->y){
        player->score += fruit->value;
        
        // Respawn fruit at a new location (for simplicity, fixed position here)
        fruit->x = (fruit->x + 3) % BOARD_WIDTH;
        fruit->y = (fruit->y + 2) % BOARD_HEIGHT;
        return 1;
    }
    return 0;
}

int main(){
    set_conio_terminal_mode();

    int childIndex = 0;
    int addChild = 0;
    Player children[20];
    for(int i = 0; i < 20; i++){
        children[i].alive = 0;
    }
    
    Player player = {
        .alive = 1,
        .x = BOARD_WIDTH / 2,
        .y = BOARD_HEIGHT / 2,
        .length = 1,
        .directionX = 0,
        .directionY = 0
    };

    Fruit fruit = {
        .x = 3,
        .y = 3,
        .value = 1
    };

    while(player.alive){
        if(kbhit())
        {
            get_player_input(&player);
        }
        if(addChild == 1){
            Player newChild = {
                .alive = 0,
                .x = childIndex == 0 ? player.x: children[childIndex - 1].x,
                .y = childIndex == 0 ? player.y: children[childIndex - 1].y,
                .length = 1,
                .directionX = player.directionX - player.directionX,
                .directionY = player.directionY - player.directionY
            };
            children[childIndex] = newChild;
            childIndex++;
            addChild = 0;
        }
        draw_board(&player, &fruit, children, childIndex);

        if (check_fruit_collision(&player, &fruit) == 1){
            addChild = 1;
            
        }
        usleep(GAME_SPEED);
    }
    printf("\033[H\033[J"); // Clear screen
    printf("Game Over! Final Score: %d\n", player.score);
    return 0;
}