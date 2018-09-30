#include <stdlib.h>
#include <stdio.h>
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
        if (m[i][0] == 'I') {
            entrance = new_coordinate(i, 0);
            return entrance;
        }
        if (m[i][columns-1] == 'I') {
            entrance = new_coordinate(i, columns-1);
            return entrance;
        }
    }
    for (i=0; i<columns; i++) {
        if (m[0][i] == 'I') {
            entrance = new_coordinate(0, i);
            return entrance;
        }
        if (m[lines-1][i] == 'I') {
            entrance = new_coordinate(lines-1, i);
        }
    }

    return entrance; /* did not find an entrance */
}

char equals_coordinates(Coordinate coord1, Coordinate coord2) {
    if ((coord1.x == coord2.x) && (coord1.y == coord2.y))
        return 1;
    return 0;
}

void print_maze(char** maze, int lines, int columns) {
    int i, j;
    for (i=0; i<lines; i++) {
        for (j=0; j<columns; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

/* Changes the array given as parameter to the possible ways the maze can continue */
/* The array must have 4 spaces */
void possibilities(Coordinate current, char** maze, Coordinate* poss_ways,
                   int lines, int columns) {
    /* Can current go down? */
    if (current.x >= lines-1)
        poss_ways[0] = new_coordinate(-1, -1);
    else {
        if (maze[current.x+1][current.y] == ' ' || maze[current.x+1][current.y] == 'O')
            poss_ways[0] = new_coordinate(current.x+1, current.y);
        else { poss_ways[0] = new_coordinate(-1, -1); }
    }

    /* Can current go up? */
    if (current.x <= 0)
        poss_ways[1] = new_coordinate(-1, -1);
    else {
        if (maze[current.x-1][current.y] == ' ' || maze[current.x-1][current.y] == 'O')
            poss_ways[1] = new_coordinate(current.x-1, current.y);
        else { poss_ways[1] = new_coordinate(-1, -1); }
    }

    /* Can current go left? */
    if (current.y <= 0)
        poss_ways[2] = new_coordinate(-1, -1);
    else {
        if (maze[current.x][current.y-1] == ' ' || maze[current.x][current.y-1] == 'O')
            poss_ways[2] = new_coordinate(current.x, current.y-1);
        else { poss_ways[2] = new_coordinate(-1, -1); }
    }

    /* Can current go right? */
    if (current.y >= columns-1)
        poss_ways[3] = new_coordinate(-1, -1);
    else {
        if (maze[current.x][current.y+1] == ' ' || maze[current.x][current.y+1] == 'O')
            poss_ways[3] = new_coordinate(current.x, current.y+1);
        else { poss_ways[3] = new_coordinate(-1, -1); }
    }
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

/* if there the maze is possible, will print the path in maze and will return
    a coordinate of value (-2, -2) 
    the coordinate of value (-2, -2) is only used to check if the exit has been found.
    the program will then use the possibilities array to determine where the exit is. */
/* else, will return the starting coordinate */
Coordinate solve(Coordinate current, char** maze, int lines, int columns) {
    int i;
    Coordinate poss[4];
    Coordinate answer;

    if (current.x == -1)
        return current;
    if (maze[current.x][current.y] == 'O')
        return new_coordinate(-2, -2);
    maze[current.x][current.y] = '*';

    /*print_maze(maze, lines, columns); printf("\n");*/

    possibilities(current, maze, poss, lines, columns);
    for (i=0; i<4; i++) {
        answer = solve(poss[i], maze, lines, columns);
        if (answer.x == -1) /* can't go this way */
            continue;
        if (answer.x == -2) /* found answer */
            return answer;
    }

    /* if the program reaches this area, the solving algorithm is going backwards in the maze */
    maze[current.x][current.y] = ' ';
    return current;
}


int main(void) {
    char   save;
    char   pathToFile[256];
    char** maze;
    int    nLines, nColumns, i, j;
    FILE*  fil;

    printf("=======================================\n");
    printf(" Maze Solver - by github.com/edusporto \n");
    printf("=======================================\n");

    do {
        /* READING WHICH FILE CONTAINS THE MAZE */
        printf("\nPlease write the path to a file containing a maze:\n");

        scanf("%255s", pathToFile);

        if ((fil = fopen(pathToFile, "r")) == NULL) {
            printf("\nCould not open file.\n");
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

        /* CLOSING THE FILE */
        fclose(fil);

        /* GETS THE ENTRANCE TO THE MAZE */
        Coordinate entrance_to_maze = get_entrance(maze, nLines, nColumns);
        Coordinate exit_to_maze = solve(entrance_to_maze, maze, nLines, nColumns);

        
        if (equals_coordinates(entrance_to_maze, exit_to_maze))
        	/* NO ANSWER TO THE MAZE */
            printf("\nThere is no answer to this maze.\n");
        else {
        	/* THERE IS AN ANSWER TO THE MAZE */
            maze[entrance_to_maze.x][entrance_to_maze.y] = 'I'; /* the I got replaced by an * */

            printf("\nThere is an answer to this maze.\n");
            print_maze(maze, nLines, nColumns);

            printf("\nWould you like to save the solved maze to a file? (Y/N)\n");
            scanf(" %c", &save);
            if (toupper(save) == 'Y') {
            	/* SAVES THE SOLVED MAZE TO A FILE */
                printf("\nPlease write the path in which the solved maze will be saved:\n");

                scanf("%255s", pathToFile);

                if ((fil = fopen(pathToFile, "w")) == NULL) {
                    printf("\nCould not open file.\n");
                } else {
                    fprintf(fil, "%d\n", nLines);
                    fprintf(fil, "%d\n", nColumns);
                    for (i=0; i<nLines; i++) {
                        for (j=0; j<nColumns; j++) 
                            fprintf(fil, "%c", maze[i][j]);
                        fprintf(fil, "\n");
                    }

                    fclose(fil);
                }
            }
        }

        /* DEALLOCATING THE MAZE */
        for (i=0; i<nLines; i++)
            free(maze[i]);
        free(maze);

    } while (stop_program() != 'Y');

    return 0;
}
