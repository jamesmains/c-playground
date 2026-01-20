#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct{
    char name[30];
    int max_hp;
    int current_hp;
    int attack;
    int gold;
    int kills;
} Entity;

#endif