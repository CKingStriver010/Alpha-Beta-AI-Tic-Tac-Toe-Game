# Alpha-Beta-AI-Tic-Tac-Toe-Game
Making of Tic Tac Toe Game with AI Algorithm(Alpha Beta Algorithm)


Step By Step Explaination of Code:
1. Global Declarations:
   Code:
     const int INF = numeric_limits<int>::max();
     struct Move { int row, col; };
     char board[3][3] = { {'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'} };
   Explanation:
    INF: Represents an infinitely large value for Minimax calculations.
    Move: A struct to store the best move’s row and column indices.
    board[3][3]: The Tic-Tac-Toe board initialized with _ (empty spaces).
2. Check if Moves Are Left
   Code:
   bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_') return true;
    return false;
   }
Explanation:
  Loops through the board to check if any moves are left.
  Returns true if an empty _ is found, otherwise returns false.
3. Evaluate Board State
   Code:
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

   Explanation:
   Checks if any row, column, or diagonal has the same character (X or O).
    Returns:
    10 if the AI (X) wins.
    -10 if the player (O) wins.
    0 if it's a draw or the game is still ongoing.
4. Minimax Algorithm with Alpha-Beta Pruning
   Code:
   int minimax(int depth, bool isMax, int alpha, int beta) {
    int score = evaluate();
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;

    if (isMax) { // AI's turn ('X')
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
    } else { // Player's turn ('O')
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

Explanation:
Base Case: If someone wins, return the evaluation score adjusted by depth (favoring quicker wins).
Recursive Case:
If isMax (AI’s turn), maximize the score.
If !isMax (player’s turn), minimize the score.
Uses Alpha-Beta Pruning to eliminate unnecessary computations.

5. Find the Best Move for AI
   Code:
   Move findBestMove(bool isMax) {
    int bestVal = isMax ? -INF : INF;
    Move bestMove = {-1, -1};

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

Explanation:
Loops through empty positions and calls minimax() to find the optimal move.
Returns the best move for the AI.

6. Printing the Board
   Code:
   void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}
Explanation:
Prints the Tic-Tac-Toe board.

7. Main Function
   Code:
   int main() {
    bool isPlayerTurn = true;

    while (isMovesLeft() && evaluate() == 0) {
        printBoard();

        if (isPlayerTurn) {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;

            if (board[row][col] == '_') board[row][col] = 'O';
            else continue; // Ignore invalid moves
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
Explanation:
Loops until the game ends.
Alternates turns between Player (O) and AI (X).
Uses findBestMove(true) to compute the AI’s move.
Prints the final result.

Example Gameplay:
INPUT:
Player Move: (0, 0)
Player Move: (1, 1)
Player Move: (2, 2)

OUTPUT:
![image](https://github.com/user-attachments/assets/8d48da5e-4f6b-4f4a-abad-ffb83191f83a)


