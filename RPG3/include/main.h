#ifndef MAIN_H
#define MAIN_H
struct GameContext;
typedef struct GameContext GameContext; // Forward declaration of GameContext
extern GameContext ctx;                 // Declare the global context so it can be used across files
#endif