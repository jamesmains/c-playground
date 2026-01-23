#include "word.h"

const Word word_list[] = {
    {.text = "programming"},
    {.text = "hangman"},
    {.text = "computer"},
    {.text = "challenge"},
    {.text = "development"},
    {.text = "function"},
    {.text = "variable"},
    {.text = "pointer"},
    {.text = "structure"},
    {.text = "algorithm"}
};

int word_list_size = sizeof(word_list) / sizeof(word_list[0]);