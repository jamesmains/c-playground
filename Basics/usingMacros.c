#include <stdio.h>
#include "readInput.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))

// Using macros AND headers, but apparently this is incorrect
// since headers should NOT contain logic.

int main(void){
    int x = readNumber("Enter a number between 0 & 99: ");
    int y = readNumber("Enter another number between 0 & 99: ");
    printf("The maximum of %d and %d is %d\n", x, y, MAX(x, y));
    return 0;
}