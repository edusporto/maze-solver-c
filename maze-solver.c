#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ================================================================= */
/*           METHODS AND STRUCTS USED IN THE PROGRAM                 */
/* ================================================================= */
typedef
    struct {
        int x, y;
    } Coordinate;

Coordinate new_coordinate(int x, int y) {
    Coordinate ret = {x, y};
    return ret;
}

/* returns a coordinate with -1 as x and -1 as y if the entrance is not found */
Coordinate get_entrance(char** m, int lines, int columns) {
    int i;
    Coordinate entrance = {-1, -1};
    
    for (i=0; i<lines; i++) {
        if (m[i][0] == 'E') {
            entrance = new_coordinate(i, 0);
            return entrance;
        }
        if (m[i][columns-1] == 'E') {
            entrance = new_coordinate(i, columns-1);
            return entrance;
        }
    }
    for (i=0; i<columns; i++) {
        if (m[0][i] == 'E') {
            entrance = new_coordinate(0, i);
            return entrance;
        }
        if (m[lines-1][i] == 'E') {
            entrance = new_coordinate(lines-1, i);
        }
    }

    return entrance; /* did not find an entrance */
}

char equals_coordinates(Coordinate coord1, Coordinate coord2) {
    if ((coord1.x == coord2.y) && (coord1.x == coord2.y))
        return 1;
    return 0;
}

/* The following 4 functions verify which ways the current coord can continue */
char can_go_down(Coordinate current, char** maze, int lines) {
    if (current.x >= lines-1) return 0;
    if (maze[current.x+1][current.y] == ' ' || maze[current.x+1][current.y] == 'S')
        return 1;
    return 0; /* can't go down */
}
char can_go_up(Coordinate current, char** maze) {
    if (current.x <= 0) return 0;
    if (maze[current.x-1][current.y] == ' ' || maze[current.x-1][current.y] == 'S')
        return 1;
    return 0;
}
char can_go_left(Coordinate current, char** maze) {
    if (current.y <= 0) return 0;
    if (maze[current.x][current.y-1] == ' ' || maze[current.x][current.y-1] == 'S')
        return 1;
    return 0;
}
char can_go_right(Coordinate current, char** maze, int columns) {
    if (current.y >= columns-1) return 0;
    if (maze[current.x][current.y+1] == ' ' || maze[current.x][current.y+1] == 'S')
        return 1;
    return 0;
}

char stop_program() {
    char answer;
    printf("\nWould you like to stop the program? (Y/N)\n");
    scanf(" %c", &answer);
    return toupper(answer);
}

/* ================================================================= */
/*                   MAIN AND SOLVER FUNCTIONS                       */
/* ================================================================= */

Coordinate solve(Coordinate current, char** maze, int lines, int columns) {
	/* TODO */
}


int main(void) {
    char   pathToFile[256];
    char** maze;
    int nLines, nColumns, i, j;
    FILE* fil;

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
        maze = (char**)malloc(sizeof(char*) * nLines);
        for (i=0; i<nLines; i++)
            maze[i] = (char*)malloc(sizeof(char) * nColumns);

        /* WRITING THE MAZE TO THE MATRIX */
        fgetc(fil);
        for (i=0; i<nLines; i++) {
            for (j=0; j<nColumns; j++) {
            maze[i][j] = fgetc(fil);
            }
            fgetc(fil);
        }

        /* GETS THE ENTRANCE TO THE MAZE */
        /*Coordinate entrance_to_maze = get_entrance(maze, nLines, nColumns);
        Coordinate exit_to_maze = solve(entrance_to_maze, maze, nLines, nColumns);

        if (equals_coordinates(entrance_to_maze, exit_to_maze))
            printf("\nThere is no answer to this maze.");
        else
            printf("There is an answer to this maze."); */



        /* prints the matrix
        for (i=0; i<nLines; i++) {
            for (j=0; j<nColumns; j++) {
                printf("%c", maze[i][j]);
            }
            printf("\n");
        }*/


        /* CLOSING THE FILE */
        fclose(fil);

        /* DEALLOCATING THE MAZE */
        for (i=0; i<nLines; i++)
            free(maze[i]);
        free(maze);

    } while (stop_program() != 'Y');

    return 0;
}
