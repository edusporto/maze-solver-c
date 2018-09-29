#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char pathToFile[256];
char* maze;
int nLines;
int nColumns;
FILE* fil;

char stopProgram() {
    char answer;
    printf("\nWould you like to stop the program? (Y/N)\n");
    scanf(" %c", &answer);
    return toupper(answer);
}

int main(void) {
    printf("=======================================\n");
    printf(" Maze Solver - by github.com/edusporto\n");
    printf("=======================================\n");

    do {
        printf("\nPlease write the path to a file containing a maze:\n");

        scanf("%255s", pathToFile);

        if (fil = fopen(pathToFile, "r") == NULL) {
            printf("Could not open file.\n\n");
            continue;
        }

        /* TODO: FIX PROBLEMS WITH READING THE FILE */
        //char teste[256];
        //fscanf(fil,"%[^\n]", teste);
        //fscanf(fil,"%[^\n]", teste);
        //printf("%s", teste);
        //fscanf(fil, "%d", &nLines);
        //fscanf(fil, "%d", &nColumns);
        //printf("%d %d\n", nLines, nColumns);

        fclose(fil);
    } while (stopProgram() != 'Y');

    return 0;
}
