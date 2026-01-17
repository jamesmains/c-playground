#include <stdio.h>

void getName()
{
    char firstName[30];

    printf("Enter your first name: \n");
    scanf("%29s", firstName);
    printf("Hello, %s!\n", firstName);
}

int main(void)
{
    getName();
    return 0;
}


