#include <stdio.h>
#include <stdbool.h>

// Function prototypes
void gameplay(int* num_of_wins_p1, int* num_of_wins_p2, char grid[3][3]);
void reset(int* num_of_wins_p1, int* num_of_wins_p2, char grid[3][3]);
void checkwin(char grid[3][3], int* num_of_wins_p1, int* num_of_wins_p2);
void drawboard(char grid[3][3]);

// Function to reset the board and scores
void reset(int* num_of_wins_p1, int* num_of_wins_p2, char grid[3][3]) {
    *num_of_wins_p1 = 0;
    *num_of_wins_p2 = 0;

    // Reset the board to empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = ' ';
        }
    }
}

// Function to check for a winner
void checkwin(char grid[3][3], int* num_of_wins_p1, int* num_of_wins_p2) {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ') {
            if (grid[i][0] == 'X') (*num_of_wins_p1)++;
            else if (grid[i][0] == 'O') (*num_of_wins_p2)++;
        }
        // Check columns
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ') {
            if (grid[0][i] == 'X') (*num_of_wins_p1)++;
            else if (grid[0][i] == 'O') (*num_of_wins_p2)++;
        }
    }

    // Check diagonals for a win
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ') {
        if (grid[0][0] == 'X') (*num_of_wins_p1)++;
        else if (grid[0][0] == 'O') (*num_of_wins_p2)++;
    }
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ') {
        if (grid[0][2] == 'X') (*num_of_wins_p1)++;
        else if (grid[0][2] == 'O') (*num_of_wins_p2)++;
    }
}

// Function to draw the board
void drawboard(char grid[3][3]) {
    printf("____________\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("  %c", grid[i][j]);
            if (j < 2) printf(" |"); // Add column separators
        }
        printf("\n");
        if (i < 2) printf("----|----|----\n"); // Add row separators
    }
    printf("____________\n");
}

// Gameplay function
void gameplay(int* num_of_wins_p1, int* num_of_wins_p2, char grid[3][3]) {
    int current_player = 1;
    char current_marker = 'X';

    while (true) { // Infinite loop for replay functionality
        drawboard(grid);

        for (int turn = 0; turn < 9; turn++) { // Maximum 9 turns in a game
            int row = 0, col = 0;
            printf("Player %d's turn (%c):\n", current_player, current_marker);

            // Ask for row and column input
            printf("Enter row (1-3): ");
            if (scanf_s("%d", &row) != 1 || row < 1 || row > 3) {
                printf("Invalid row input! Try again.\n");
                while (getchar() != '\n'); // Clear the input buffer
                turn--; // Retry the current turn
                continue;
            }

            printf("Enter column (1-3): ");
            if (scanf_s("%d", &col) != 1 || col < 1 || col > 3) {
                printf("Invalid column input! Try again.\n");
                while (getchar() != '\n'); // Clear the input buffer
                turn--; // Retry the current turn
                continue;
            }

            // Adjust for 0-based indexing
            row -= 1;
            col -= 1;

            // Check if slot is already occupied
            if (grid[row][col] != ' ') {
                printf("Slot already occupied! Try again.\n");
                turn--;
                continue;
            }

            // Place marker
            grid[row][col] = current_marker;

            // Draw the board
            drawboard(grid);

            // Check for a winner
            checkwin(grid, num_of_wins_p1, num_of_wins_p2);
            if (*num_of_wins_p1 > 0) {
                printf("Player 1 wins!\n");
                break;
            }
            if (*num_of_wins_p2 > 0) {
                printf("Player 2 wins!\n");
                break;
            }

            // Swap player and marker
            current_player = (current_player == 1) ? 2 : 1;
            current_marker = (current_marker == 'X') ? 'O' : 'X';
        }

        // If no winner, declare a tie
        if (*num_of_wins_p1 == 0 && *num_of_wins_p2 == 0) {
            printf("It's a tie!\n");
        }

        // Ask if players want to play again or reset
        char choice = '\0';
        printf("Do you want to play again (y/n)? ");
        if (scanf_s(" %c", &choice, 1) != 1 || (choice != 'y' && choice != 'n')) {
            printf("Invalid input! Defaulting to 'n'.\n");
            choice = 'n';
        }
        if (choice == 'n') {
            break; // Exit the game loop
        }

        // Reset scores and board for the next game
        reset(num_of_wins_p1, num_of_wins_p2, grid);
    }
}

// Main function
int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int num_of_wins_p1 = 0;
    int num_of_wins_p2 = 0;

    gameplay(&num_of_wins_p1, &num_of_wins_p2, board);

    return 0;
}
