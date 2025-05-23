#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std; 

bool helpNInARow(const Scaffold& s, int col, int level, int deltaCol, int deltaLevel, int N, int color) {
    // Start from first instance of color (col, level)
    // Check bounds and call checkerAt() to see if there's a checker in 4 directions + diagonally
    int inARow = 1;    // Count the starting cell

    for (int i = 1; i < N; i++) {
        int nextCol = col + i * deltaCol;
        int nextLevel = level + i * deltaLevel;

        // Check bounds 
        if (nextCol < 1 || nextCol > s.cols() || nextLevel < 1 || nextLevel > s.levels()) {
            break;
        }
        // Check color match 
        if (s.checkerAt(nextCol, nextLevel) == color) {
            inARow++;
        }
        else {
            break;
        }
    }
    return (inARow == N);
}

bool checkGameOver(const Scaffold& s, int N, int& winner) {
    // Check for a win
    // Loop through each cell
    // Check if that cell is occupied 
    // Call helpNInARow() from that position

    // If there are no empty slots left, declare a tie 
    if (s.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }
    
    for (int col = 1; col <= s.cols(); col++) {
        for (int level = 1; level <= s.levels(); level++) {
            int color = s.checkerAt(col, level);
            if (color == RED || color == BLACK) {
                // Going RIGHT  
                if (helpNInARow(s, col, level, 1, 0, N, color)) {
                    winner = color;
                    return true;
                }
                // Going UP 
                else if (helpNInARow(s, col, level, 0, 1, N, color)) {
                    winner = color;
                    return true;
                }
                // Going RIGHT-UP 
                else if (helpNInARow(s, col, level, 1, 1, N, color)) {
                    winner = color;
                    return true;
                }
                // Going RIGHT-DOWN 
                else if (helpNInARow(s, col, level, 1, -1, N, color)) {
                    winner = color;
                    return true;
                }
            }
        }
    }
    return false;
}
int makeComputerMove(const Scaffold& s, int N, int color, int depth) {
    Scaffold tempS = s;
    pair <int, int> result = determineBestComputerMove(tempS, N, color, depth);
    return result.first;
}

/*
int makeComputerMove(const Scaffold& s, int N, int color, int depth, int smartColor, int& bestCol, int& winner) {
    int bestScore;
    int bestDepth = INT_MAX;
    int tempScore = 0;
    int tempCol = 0;
    int nextColor = VACANT;

    if (color == smartColor) {
        bestScore = INT_MIN;    // Worst case, I'll try to beat it
    }

    else {
        bestScore = INT_MAX;
    }
	for (int i = 1; i <= s.cols(); i++) {
        // Make move 
		if (s.makeMove(i, color)) {
			// Make variable for checkGameOver with who just won 
            bool gameOver = checkGameOver(s, N, winner);

            // If the game is over, declare winner and track score 
            if (gameOver) {
                // bool gameOver = checkGameOver(s, N, winner);
                // If bot won
                if (winner == smartColor) {
                    tempScore = INT_MAX - depth;
                }
                // If tie
                else if (winner == TIE_GAME) {
                    tempScore = 0;
                }
                // If human won 
                else {
                    tempScore = -(INT_MAX - depth);
                }
            }

            // Recall RECURSIVE function with updated scaffold, switched color, depth + 1
            else {
                if (color == RED) {
                    nextColor = BLACK;
                }
                else if (color == BLACK) {
                    nextColor = RED;
                }
                int dummyCol;   // So we don't forget the current best move
                tempScore = makeComputerMove(s, N, nextColor, depth + 1, smartColor, dummyCol, winner);
            }
            
            // Undo move
            s.undoMove();

            // Use returned score to decide if move I just tried is better than the best so far 
            // If current color is bot's color, maximize score
            if (color == smartColor) {
                if (tempScore > bestScore || (tempScore == bestScore && depth < bestDepth)) {
                    bestScore = tempScore;
                    bestCol = i;
                    bestDepth = depth;
                }
            }

            // If current color is opponent's color, minimize score 
            else {
                if (tempScore < bestScore || (tempScore == bestScore && depth > bestDepth)) {
                    bestScore = tempScore;
                    bestCol = i; 
                    bestDepth = depth;
                }
            }

		}
	}
	return bestScore;


}
    */

// Return best column and best score 
pair<int, int> determineBestComputerMove(Scaffold& s, int N, int color, int depth) {
    int bestCol = 0;
    int bestScore = INT_MIN;
    int winner = VACANT;
    //int bestDepth = INT_MAX;
    int tempScore = 0;
    //int nextColor = VACANT;

    // Iterate through all possible moves the computer can make 
    for (int col = 1; col <= s.cols(); col++) {
        if (!s.makeMove(col, color)) {
            continue;
        }

        // Make variable for checkGameOver with who just won 
        bool gameOver = checkGameOver(s, N, winner);
        if (gameOver) {
            // Rate scaffold after move has been made
            // bool gameOver = checkGameOver(s, N, winner);
            // If bot won
            if (winner == color) {
                tempScore = INT_MAX - depth;
            }
            // If tie
            else if (winner == TIE_GAME) {
                tempScore = 0;
            }
            // If human won 
            else {
                tempScore = -(INT_MAX - depth);
            }
        }
        // If game isn't over...
        else {
            // Switch player
            if (color == RED) {
                color = BLACK;
            }
            else if (color == BLACK) {
                color = RED;
            }
            //int dummyCol;   Because that's gonna be in determineBestHumanMove's return 
            // Recurse with determineBestHumanMove()
            pair<int, int> result = determineBestHumanMove(s, N, color, depth + 1);
            tempScore = result.second;  // Remember the result for each human move 
        }
                    
        // Choose move that results in scaffold with max value
        if (tempScore > bestScore) {    // tempScore includes depth 
            bestScore = tempScore;
            bestCol = col;
        }
        // Undo computer's trial move
        s.undoMove();
    }
    
    return make_pair(bestCol, bestScore);
}

pair<int, int> determineBestHumanMove(Scaffold& s, int N, int color, int depth) {
    // Probably just determineBestComputerMove() but flipped

    int bestCol = 0;
    int bestScore = INT_MAX;    // Because human is tryna pick computer's worst score
    int winner = VACANT;
    //int bestDepth = INT_MAX;
    int tempScore = 0;
    //int nextColor = VACANT;

    // Iterate through all possible moves the computer can make 
    for (int col = 1; col <= s.cols(); col++) {
        if (!s.makeMove(col, color)) {
            continue;
        }

        // Make variable for checkGameOver with who just won 
        bool gameOver = checkGameOver(s, N, winner);
        if (gameOver) {
            // Rate scaffold after move has been made
            // bool gameOver = checkGameOver(s, N, winner);
            // If bot won
            if (winner == color) {
                tempScore = -(INT_MAX - depth); 
            }
            // If tie
            else if (winner == TIE_GAME) {
                tempScore = 0;
            }
            // If human won 
            else {
                tempScore = INT_MAX - depth;
            }
        }
        // If game isn't over...
        else {
            // Switch player
            if (color == RED) {
                color = BLACK;
            }
            else if (color == BLACK) {
                color = RED;
            }
            //int dummyCol;   Because that's gonna be in determineBestHumanMove's return 
            // Recurse with determineBestHumanMove()
            pair<int, int> result = determineBestComputerMove(s, N, color, depth + 1);
            tempScore = result.second;  // Remember the result for each human move 
        }

        // Choose move that results in scaffold with minimum value (means human wins)
        if (tempScore < bestScore) {    // tempScore includes depth 
            bestScore = tempScore;
            bestCol = col;
        }
        // Undo computer's trial move
        s.undoMove();
    }

    return make_pair(bestCol, bestScore);
}
