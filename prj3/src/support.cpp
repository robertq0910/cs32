#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std;

// JumpyTimer class implementations
JumpyTimer::JumpyTimer(int jumpInterval)
    : m_jumpInterval(jumpInterval), m_callsMade(0)
{
    actualElapsed();
}
double JumpyTimer::elapsed()
{
    m_callsMade++;
    if (m_callsMade == m_jumpInterval)
    {
        m_lastElapsed = m_timer.elapsed();
        m_callsMade = 0;
    }
    return m_lastElapsed;
}
double JumpyTimer::actualElapsed()
{
    m_lastElapsed = m_timer.elapsed();
    return m_lastElapsed;
}

// Helper functions 
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

    // If there are no empty slots left, declare a tie 
    if (s.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }

    return false;
}

// The hard functions
int makeComputerMove(const Scaffold& s, int N, int color, int depth, double timeLimit, JumpyTimer& timer) {
    Scaffold tempS = s;
    // Recursive function with timeLimit and time 
    pair <int, int> result = determineBestComputerMove(tempS, N, color, depth, timeLimit, timer);
    return result.first;
}

// Return best column and best score 
pair<int, int> determineBestComputerMove(Scaffold& s, int N, int color, int depth, double timeLimit, JumpyTimer& timer) {
    int bestCol = -1;
    int bestScore = INT_MIN;
    int winner = VACANT;
    int tempScore = 0;

    // Iterate through all possible moves the computer can make 
    for (int col = 1; col <= s.cols(); col++) {
        if (!s.makeMove(col, color)) {
            continue;
        }

        // Make variable for checkGameOver with who just won 
        bool gameOver = checkGameOver(s, N, winner);
        if (gameOver) {
            // If bot won
            if (winner == color) {
                tempScore = INT_MAX - depth;
                //temp.undoMove();
            }
            // If tie
            else if (winner == TIE_GAME) {
                tempScore = 0;
                //temp.undoMove();
            }
            // If human won 
            else {
                tempScore = -(INT_MAX - depth);
                //temp.undoMove();
            }
            //break;
        }
        // If game isn't over...
        else {
            // Save start time so can compute time this branch takes
            double startTime = timer.elapsed();
            // Explore this branch by recursing with determineBestHuman()
            pair<int, int> result = determineBestHumanMove(s, N, color == RED ? BLACK : RED, depth + 1, timeLimit, timer);
            // Adjust remaining time
            timeLimit -= (timer.elapsed() - startTime);
            tempScore = result.second;  // Remember the result for each human move 


        }

        // Choose move that results in scaffold with max value
        if (tempScore > bestScore) {    // tempScore includes depth 
            bestScore = tempScore;
            bestCol = col;
        }
        //Undo computer's trial move
            s.undoMove();
        if (timeLimit <= 0) break;

    }
    //cerr << bestCol << " ";
    return make_pair(bestCol, bestScore);
}

pair<int, int> determineBestHumanMove(Scaffold& s, int N, int color, int depth, double timeLimit, JumpyTimer& timer) {
    int bestCol = 1;
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
            // Save start time so can compute time this branch takes
            double startTime = timer.elapsed();
            // Explore this branch by recursing with determineBestHuman()
            pair<int, int> result = determineBestComputerMove(s, N, color == RED ? BLACK : RED, depth + 1, timeLimit, timer);
            // Adjust remaining time
            timeLimit -= (timer.elapsed() - startTime);

            if (timeLimit <= 0) {
                s.undoMove();
                break;  // Exit early if you're out of time 
            }

            tempScore = result.second;
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
