#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10

// Function prototypes
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY);
void displayGrid(char grid[GRID_SIZE][GRID_SIZE]);
void movePlayer(char grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY, int* lives, int* moves);

int main() {
    printf("First Project run locally");
    char grid[GRID_SIZE][GRID_SIZE];
    int playerX, playerY;
    int lives = 3; // Starting lives
    int moves = 0; // Move counter

    srand((unsigned int)time(0)); // Safely seed random number generator

    initializeGrid(grid, &playerX, &playerY);

    while (lives > 0) {
        system("cls"); // Clear console for better grid display (use "clear" on Linux/Mac)
        displayGrid(grid);
        printf("Lives: %d | Moves: %d\n", lives, moves);
        movePlayer(grid, &playerX, &playerY, &lives, &moves);
    }

    printf("Game over! You survived %d moves.\n", moves);

    return 0;
}

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY) {
    // Fill grid with empty spaces
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    // Place random landmines
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != '.'); // Ensure landmine doesn't overwrite other elements
        grid[x][y] = '*';
    }

    // Occasionally place bonus lives
    if (rand() % 2) { // 50% chance of bonus life being placed
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != '.'); // Ensure bonus doesn't overwrite other elements
        grid[x][y] = '+';
    }

    // Place player on the grid
    *playerX = 0; // Starting position
    *playerY = 0;
    grid[*playerX][*playerY] = '@';
}

void displayGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void movePlayer(char grid[GRID_SIZE][GRID_SIZE], int* playerX, int* playerY, int* lives, int* moves) {
    char move;
    printf("Enter move (w/a/s/d): ");
    if (scanf(" %c", &move) != 1) { // Validate input
        printf("Invalid input! Use w/a/s/d.\n");
        return;
    }

    // Clear current position
    grid[*playerX][*playerY] = '.';

    // Update position based on input
    if (move == 'w' && *playerX > 0) (*playerX)--;
    else if (move == 's' && *playerX < GRID_SIZE - 1) (*playerX)++;
    else if (move == 'a' && *playerY > 0) (*playerY)--;
    else if (move == 'd' && *playerY < GRID_SIZE - 1) (*playerY)++;
    else {
        printf("Invalid move! Out of bounds.\n");
        return;
    }

    // Check new position
    if (grid[*playerX][*playerY] == '*') {
        printf("Boom! You hit a landmine!\n");
        (*lives)--;
    }
    else if (grid[*playerX][*playerY] == '+') {
        printf("Lucky you! You found an extra life!\n");
        (*lives)++;
    }

    // Update player position
    grid[*playerX][*playerY] = '@';
    (*moves)++;

}
