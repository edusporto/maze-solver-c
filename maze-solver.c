#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char pathToFile[256];
char** maze;
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
    int i, j;

    printf("=======================================\n");
    printf(" Maze Solver - by github.com/edusporto\n");
    printf("=======================================\n");

    do {
        /* READING WHICH FILE CONTAINS THE MAZE */
        printf("\nPlease write the path to a file containing a maze:\n");

        scanf("%255s", pathToFile);

        if ((fil = fopen(pathToFile, "r")) == NULL) {
            printf("Could not open file.\n\n");
            continue;
        }

        /* READING THE DIMENSIONS OF THE MAZE */
        fscanf(fil, "%d", &nLines);
        fscanf(fil, "%d", &nColumns);

        /* ALLOCATING THE MATRIX OF THE MAZE */
        maze = (int**)malloc(sizeof(char*) * nLines);
        for (i=0; i<nLines; i++)
            maze[i] = (int*)malloc(sizeof(char) * nColumns);

        /* WRITING THE MAZE TO THE MATRIX */
        fgetc(fil);
        for (i=0; i<nLines; i++) {
            for (j=0; j<nColumns; j++) {
                maze[i][j] = fgetc(fil);
            }
            fgetc(fil);
        }


        // printing the maze (will be removed)
        for (i=0; i<nLines; i++) {
            for (j=0; j<nColumns; j++) {
                printf("%c", maze[i][j]);
            }
            printf("\n");
        }


        /* CLOSING THE FILE */
        fclose(fil);

        /* DEALLOCATING THE MAZE */
        for (i=0; i<nLines; i++)
            free(maze[i]);
        free(maze);

    } while (stopProgram() != 'Y');

    return 0;
}
