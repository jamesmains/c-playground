
#include <stdio.h>

int readNumber(char message[]){
    int value;

    printf("%s\n", message);
    if (scanf("%d", &value) != 1) {
        // Basic error handling if user types a letter
        printf("Invalid input!\n");
    }
    return value;
}