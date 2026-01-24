#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s [add|list|clear]\n", argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "add") == 0){
        if(argc < 3){
            printf("Error: Please task description.\n");
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
    else{
        printf("Unknown command: %s", argv[1]);
    }
    return 0;
}