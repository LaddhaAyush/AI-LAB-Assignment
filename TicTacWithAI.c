#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PLAYER 'X'
#define AI 'O'
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

int evaluate() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == PLAYER) return -10;
        }
    }
    
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == PLAYER) return -10;
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == PLAYER) return -10;
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == PLAYER) return -10;
    }
    
    return 0;
}

int minimax(int depth, int isMax) {
    int score = evaluate();
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;
    
    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = INT_MIN;
    int row = -1, col = -1;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(0, 0);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = AI;
}

void playerMove() {
    int row, col;
    printf("Enter row (0-2) and column (0-2): ");
    scanf("%d %d", &row, &col);
    if (board[row][col] == EMPTY)
        board[row][col] = PLAYER;
    else {
        printf("Invalid move, try again.\n");
        playerMove();
    }
}

int main() {
    initializeBoard();
    printBoard();
    
    while (isMovesLeft()) {
        playerMove();
        printBoard();
        if (evaluate() == -10) {
            printf("You win!\n");
            break;
        }
        if (!isMovesLeft()) break;
        
        printf("AI is making a move...\n");
        findBestMove();
        printBoard();
        if (evaluate() == 10) {
            printf("AI wins!\n");
            break;
        }
    }
    
    if (evaluate() == 0)
        printf("It's a draw!\n");
    
    return 0;
}
