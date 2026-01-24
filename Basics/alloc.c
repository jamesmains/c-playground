#include <stdio.h>
#include <stdlib.h>

int main(){
    // Start small
    int capacity = 5;                            // Initialize the capacity for the container
    char *str = malloc(capacity * sizeof(char)); // Initialize the container for the final output

    if (str == NULL) return 1; // Check if RAM is full

    printf("Start typing and the allocation will grow as needed.\n");

    int length = 0; // Initialize the length of the input
    char c;         // Char to contain the individual keys.

    // Capture input & resize as needed
    while((c = getchar()) != '\n' && c != EOF){

        // Need to resize the str capacity in RAM.
        if(length + 1 >= capacity){
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
            printf("[DEBUG] Growing buffer to %d bytes.\n", capacity);
        }
        str[length++] = c;
    }

    str[length] = '\0';

    printf("You entered: %s\n", str);
    printf("Final size: %d bytes.\n", capacity);

    // ALWAYS free it, otherwise a memory leak will occur
    free(str);

    return 0;
}