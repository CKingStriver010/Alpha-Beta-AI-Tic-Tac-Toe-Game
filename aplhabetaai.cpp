#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Move {
    int row, col;
};

char board[3][3] = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'X') return 10;
            else if (board[row][0] == 'O') return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'X') return 10;
            else if (board[0][col] == 'O') return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return 10;
        else if (board[0][0] == 'O') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return 10;
        else if (board[0][2] == 'O') return -10;
    }
    return 0;
}

int minimax(int depth, bool isMax, int alpha, int beta) {
    int score = evaluate();
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;
    if (isMax) {
        int best = -INF;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    best = max(best, minimax(depth + 1, false, alpha, beta));
                    board[i][j] = '_';
                    alpha = max(alpha, best);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    } else {
        int best = INF;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    best = min(best, minimax(depth + 1, true, alpha, beta));
                    board[i][j] = '_';
                    beta = min(beta, best);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

Move findBestMove(bool isMax) {
    int bestVal = isMax ? -INF : INF;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = isMax ? 'X' : 'O';
                int moveVal = minimax(0, !isMax, -INF, INF);
                board[i][j] = '_';
                if ((isMax && moveVal > bestVal) || (!isMax && moveVal < bestVal)) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {
    bool isPlayerTurn = true;
    while (isMovesLeft() && evaluate() == 0) {
        printBoard();
        if (isPlayerTurn) {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (board[row][col] == '_') board[row][col] = 'O';
            else continue;
        } else {
            Move bestMove = findBestMove(true);
            board[bestMove.row][bestMove.col] = 'X';
        }
        isPlayerTurn = !isPlayerTurn;
    }
    printBoard();
    int result = evaluate();
    if (result == 10) cout << "Computer wins!" << endl;
    else if (result == -10) cout << "You win!" << endl;
    else cout << "It's a draw!" << endl;
    return 0;
}