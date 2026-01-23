#include <stdio.h>
#include "database.h"
#include <stdlib.h>
#include <time.h>

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
    srand((unsigned int)time(NULL));
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
        for (int w = 0; word.text[w] != '\0'; w++) {
            int found = 0;
            for (int g = 0; g < guessIndex; g++) {
                if(word.text[w] == guesses[g]) {
                    found = 1;
                    break;
                }
            }
            if(!found) break;
            if(word.text[w + 1] == '\0') {
                printf("\nCongratulations! You guessed the word: %s\n", word.text);
                return 0;
            }
        }
    }
    printf("\nGame Over! The word was: %s\n", word.text);
    return 0;
}