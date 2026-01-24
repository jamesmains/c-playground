#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s [add|list|clear]\n", argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "add") == 0){
        if(argc < 3){
            printf("Error: Please add task description.\n");
            return 1;
        }
        printf("Adding task: %s", argv[2]);
        FILE *file = fopen("tasks.txt", "a");
        if(file == NULL){
            perror("Could not open file.");
            return 1;
        }
        fprintf(file, "%s\n", argv[2]);
        fclose(file);
    }
    else if(strcmp(argv[1],"remove") == 0){
        if(argc < 3){
            printf("Error: Please indicate which task you want removed by number.");
            return 1;
        }
        int targetIndex = atoi(argv[2]); // The # of the task to delete
    
    FILE *file = fopen("tasks.txt", "r");      // Read from original
    FILE *fileTemp = fopen("temp.txt", "w");   // Write to temp
    
    if (file == NULL || fileTemp == NULL) {
        perror("Error opening files");
        return 1;
    }

    char buff[256];
    int currentIndex = 1; // Start at 1 to match your 'list' command

    while (fgets(buff, sizeof(buff), file))
    {
        // Only write to the temp file if it's NOT the target
        if (currentIndex != targetIndex)
        {
            fprintf(fileTemp, "%s", buff);
        }
        currentIndex++;
    }

    fclose(file);
    fclose(fileTemp);

    // The Magic Swap:
    remove("tasks.txt");             // Delete the old file
    rename("temp.txt", "tasks.txt"); // Rename temp to tasks.txt

    printf("Task #%d removed.\n", targetIndex);
    }
    else if (strcmp(argv[1], "list") == 0){
        printf("Listing all tasks...\n");
        FILE *file = fopen("tasks.txt", "r");
        if(file == NULL){
            perror("Could not open file.");
            return 1;
        }
        char buff[256];
        while(fgets(buff,sizeof(buff),file)){
            printf("%s",buff);
        }
        fclose(file);
    }
    else if (strcmp(argv[1], "clear") == 0){
        printf("Clearing all tasks\n");
        FILE *file = fopen("tasks.txt", "w");
        if (file == NULL) {
            perror("Could not open file.");
            return 1;
        }
        fclose(file);
    }
    else{
        printf("Unknown command: %s", argv[1]);
    }
    return 0;
}