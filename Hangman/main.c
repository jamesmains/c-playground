#include <stdio.h>
#include "database.h"
#include <stdlib.h>

void draw_screen(Word* word, char* guesses, int guessCount) {
    for(int i = 0; word->text[i] != '\0'; i++) { // Loop until the end of the string
        int found = 0;
        for (int j = 0; j < guessCount; j++) {
            if(word->text[i] == guesses[j]) {
                found = 1;
                break;
            }
        }
        if(found) printf("%c ", word->text[i]);
        else printf("_ ");
    }
}

int main(){
    char guesses[30];
    int guessIndex = 0;
    Word word = word_list[rand() % word_list_size];
    int guessesRemaining = 6;
    while(guessesRemaining > 0){
        printf("\nGuesses remaining: %d\n", guessesRemaining);
        draw_screen(&word, guesses, guessIndex);

         // Check for win condition
        char guess;
        printf("\nEnter your guess: ");
        scanf(" %c", &guess);

        guesses[guessIndex++] = guess;
        // Check if guess is in word
        int correct = 0;
        for(int i = 0; i < sizeof(word.text); i++){
            if(word.text[i] == guess){
                correct = 1;
                break;
            }
        }
        if(!correct){
            guessesRemaining--;
        }
    }
    // scanf("%29s", word);
    return 0;
}