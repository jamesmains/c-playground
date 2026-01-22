#ifndef PLAYER_H
#define PLAYER_H
typedef struct Player {
    int alive;
    int x;
    int y;
    int length;
    int directionX;
    int directionY;
    int score;
} Player;
#endif