#include <stdio.h>

#define PLAYER1 'X'
#define PLAYER2 'O'
#define EMPTY ' '

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = EMPTY;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}

int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return 1;
    return 0;
}

int checkWinner() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != EMPTY)
            return board[row][0];
    }
    
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != EMPTY)
            return board[0][col];
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0];
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2];
    
    return 0;
}

void playerMove(char player) {
    int row, col;
    printf("Player %c, enter row (0-2) and column (0-2): ", player);
    scanf("%d %d", &row, &col);
    if (board[row][col] == EMPTY)
        board[row][col] = player;
    else {
        printf("Invalid move, try again.\n");
        playerMove(player);
    }
}

int main() {
    initializeBoard();
    printBoard();
    char currentPlayer = PLAYER1;
    
    while (isMovesLeft()) {
        playerMove(currentPlayer);
        printBoard();
        if (checkWinner()) {
            printf("Player %c wins!\n", currentPlayer);
            return 0;
        }
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }
    
    printf("It's a draw!\n");
    return 0;
}
