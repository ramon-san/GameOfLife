#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define ROWS 48
#define COLS 175
#define GENERATIONS 1000
#define SPEED 250000 // 1 second = 1000000 microseconds

void red();
void setLimits(char universe[ROWS][COLS]);
void printUniverse(char universe[ROWS][COLS]);
void initialConditions(char universe[ROWS][COLS], float distribution);
void checkConditions(char universe[ROWS][COLS], int results[(ROWS-2)*(COLS-2)]);
int getResult(char input);
void changeOrder(char universe[ROWS][COLS], int results[(ROWS-2)*(COLS-2)]);

/**
 * Main function of our code.
 * 
 * @param argv the program expects a number between 0 and 1 when running the code.
 * 
 */
int main(int argc, char *argv[]) {
    char universe[ROWS][COLS];
    float distribution = atof(argv[1]);
    srand(time(NULL));

    if (argv[1] == NULL || distribution < 0 || distribution > 1) {
        red();
        printf("\nERROR: Please specify a valid distribution.\n\n");
        return (1);
    }
    setLimits(universe);
    printf("\nGenerating game with %.0f%% distribution...\n\n", (distribution*100));
    initialConditions(universe, distribution);
    printUniverse(universe);
    for (int i = 0; i < GENERATIONS; i++) {
        int results[(ROWS-2)*(COLS-2)];
        checkConditions(universe, results);
        changeOrder(universe, results);
        printUniverse(universe);
    }
    return (0);
}

/**
 * Function that sets limits to our space.
 * 
 * @param universe two dimensional space.
 * 
 */
void setLimits(char universe[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 || i == ROWS-1) {
                universe[i][j] = '-';
            } else if (j == 0 || j == COLS-1) {
                universe[i][j] = '|';
            } else {
                universe[i][j] = ' ';
            }
        }
    }
}

/**
 * Function that prints out current state of our universe.
 * 
 * @param universe two dimensional space.
 * 
 */
void printUniverse(char universe[ROWS][COLS]) {
    usleep(SPEED);
    printf("\n\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", universe[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/**
 * Function that starts our universe based on given distribution.
 * 
 * @param universe two dimensional space.
 * @param distribution percentage of living cells at the begining.
 * 
 */
void initialConditions(char universe[ROWS][COLS], float distribution) {
    for (int i = 1; i < ROWS-1; i++) {
        for (int j = 1; j < COLS-1; j++) {
                if (((float)(rand())/RAND_MAX) <= distribution) {
                    universe[i][j] = '*';
                } else universe [i][j] = ' ';
        }
    }
}

/**
 * Function that gives next state to the universe; keep in mind:
 *    Upper left limit     [1][1] 
 *    Upper right limit    [1][COLS-2]
 *    Lower left limit     [ROWS-2][1]
 *    Lower right limit    [ROWS-2][COLS-2]
 * 
 * @param universe two dimensional space.
 * @param results array with results from neighboring cell count.
 * 
 */
void checkConditions(char universe[ROWS][COLS], int results[(ROWS-2)*(COLS-2)]) {
    int matrixPos = 0;
    for (int row = 1; row < ROWS-1; row++) {
        for (int col = 1; col < COLS-1; col++) {
            int counter = 0;
            for (int pos = 0; pos < 8; pos++) {
                switch (pos) {
                case 0: // Check upper left.
                    if (row-1 == 0 && col-1 == 0) {
                        counter += getResult(universe[ROWS-2][COLS-2]);
                    } else if (row-1 == 0) {
                        counter += getResult(universe[ROWS-2][col-1]);
                    } else if (col-1 == 0) {
                        counter += getResult(universe[row-1][COLS-2]);
                    } else {
                        counter += getResult(universe[row-1][col-1]);
                    }
                    break;
                case 1: // Check upper center.
                    if (row-1 == 0) {
                        counter += getResult(universe[ROWS-2][col]);
                    } else {
                        counter += getResult(universe[row-1][col]);
                    }
                    break;
                case 2: // Check upper right.
                    if (row-1 == 0 && col+1 == COLS-1) {
                        counter += getResult(universe[ROWS-2][1]);
                    } else if (row-1 == 0) {
                        counter += getResult(universe[ROWS-2][col+1]);
                    } else if (col+1 == COLS-1) {
                        counter += getResult(universe[row-1][1]);
                    } else {
                        counter += getResult(universe[row-1][col+1]);
                    }
                    break;
                case 3: // Check center left.
                    if (col-1 == 0) {
                        counter += getResult(universe[row][COLS-2]);
                    } else {
                        counter += getResult(universe[row][col-1]);
                    }
                    break;
                case 4: // Check center right.
                    if (col+1 == COLS-1) {
                        counter += getResult(universe[row][1]);
                    } else {
                        counter += getResult(universe[row][col+1]);
                    }
                    break;
                case 5: // Check buttom left.
                    if (row+1 == ROWS-1 && col-1 == 0) {
                        counter += getResult(universe[1][COLS-2]);
                    } else if (row+1 == ROWS-1) {
                        counter += getResult(universe[1][col-1]);
                    } else if (col-1 == 0) {
                        counter += getResult(universe[row+1][COLS-2]);
                    } else {
                        counter += getResult(universe[row+1][col-1]);
                    }
                    break;
                case 6: // Check buttom center.
                    if (row+1 == ROWS-1) {
                        counter += getResult(universe[1][col]);
                    } else {
                        counter += getResult(universe[row+1][col]);
                    }
                    break;
                case 7: // Check buttom right.
                    if (row+1 == ROWS-1 && col+1 == COLS-1) {
                        counter += getResult(universe[1][1]);
                    } else if (row+1 == ROWS-1) {
                        counter += getResult(universe[1][col+1]);
                    } else if (col+1 == COLS-1) {
                        counter += getResult(universe[row+1][1]);
                    }else {
                        counter += getResult(universe[row+1][col+1]);
                    }
                    break;
                }
            }
            results[matrixPos] = counter;
            matrixPos++;
        }
    }
}

/**
 * Function that changes the values of the matrix.
 * 
 * @param universe two dimensional space.
 * @param results array with results from neighboring cell count.
 * 
 */
void changeOrder(char universe[ROWS][COLS], int results[(ROWS-2)*(COLS-2)]) {
    int position = 0;
    for (int row = 1; row < ROWS-1; row++) {
        for (int col = 1; col < COLS-1; col++) {
            if (universe[row][col] == '*' && results[position] >= 2 && results[position] <= 3) {
                universe[row][col] = '*';
            } else if (universe[row][col] == ' ' && results[position] == 3) {
                universe[row][col] = '*';
            } else universe[row][col] = ' ';
            position++;
        }
    }

}
 
/**
 * Function that checks if a given cell is alive or dead.
 * 
 * @param input content of a given neighboring cell.
 * 
 * @return 1 if cell is alive and 0 if cell is dead.
 * 
 */
int getResult(char input) {
    if (input == '*') return (1);
    else return (0);
}

/**
 * Function to make terminal output red, must be declared before printf().
 * 
 */
void red() {
    printf("\033[1;31m");
}