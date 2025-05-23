// Game.cpp

#include "provided.h"
#include <iostream>
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private: 
    Scaffold m_scaffold;
    Player* m_red;
    Player* m_black;
    Player* m_currentPlayer;
    int m_cols;
    int m_levels;
    int m_N;
    int m_currentColor;
    bool NInARow(const Scaffold& s, int col, int level, int deltaCol, int deltaLevel, int N, int color) const;
    int currentColor() const;
};


GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) :m_scaffold(nColumns, nLevels), m_cols(nColumns), m_levels(nLevels), m_N(N), m_red(red), m_black(black), m_currentColor(RED)
// Initializer list constructs a scaffold 
{
    if (m_N < 1) {
        cerr << "Invalid # in a row";
        exit(1);
    }
    m_currentPlayer = m_red;

}

int GameImpl::currentColor() const {
    return (m_currentPlayer == m_red ? RED : BLACK);
}

bool GameImpl::NInARow(const Scaffold& s, int col, int level, int deltaCol, int deltaLevel, int N, int color) const {
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

bool GameImpl::completed(int& winner) const
{
    // Check for a win
    // Loop through each cell
    // Check if that cell is occupied 
    // Call NInARow() from that position
    int count = 0;
    for (int col = 1; col <= m_scaffold.cols(); col++) {
        for (int level = 1; level <= m_scaffold.levels(); level++) {
            int color = m_scaffold.checkerAt(col, level);
            if (checkerAt(col, level) == RED || checkerAt(col, level) == BLACK) {
                // Going RIGHT  
                if (NInARow(m_scaffold, col, level, 1, 0, m_N, color)) {
                    return true;
                }
                // Going LEFT 
                else if (NInARow(m_scaffold, col, level, -1, 0, m_N, color)) {
                    return true;
                }
                // Going UP 
                else if (NInARow(m_scaffold, col, level, 0, 1, m_N, color)) {
                    return true;
                }
                // Going DOWN 
                else if (NInARow(m_scaffold, col, level, 0, -1, m_N, color)) {
                    return true;
                }
                // Going RIGHT-UP 
                else if (NInARow(m_scaffold, col, level, 1, 1, m_N, color)) {
                    return true;
                }
                // Going LEFT-UP 
                else if (NInARow(m_scaffold, col, level, -1, 1, m_N, color)) {
                    return true;
                }
                // Going RIGHT-DOWN 
                else if (NInARow(m_scaffold, col, level, 1, -1, m_N, color)) {
                    return true;
                }
                // Going LEFT-DOWN 
                else if (NInARow(m_scaffold, col, level, -1, -1, m_N, color)) {
                    return true;
                }
            }
        }
    }
    if (m_scaffold.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }
    return false;
}

bool GameImpl::takeTurn()
{
    int tempWinner;
    // If the game is over, return false
    if (completed(tempWinner)) {
        return false;
    }
    // Otherwise, make a move for the player whose turn it is (so that it becomes the other player's turn) and return true.
    int move = m_currentPlayer->chooseMove(m_scaffold, m_N, currentColor());
    m_scaffold.makeMove(move, currentColor());
}

void GameImpl::play()
{
    int winner;
    // If the game isn't done 
    while (!completed(winner)) {
        // If the current player is human
        if (m_currentPlayer->isInteractive())
            // Cout your move 
            cout << "Your move! Enter a column number: ";
        // If the current player is a bot 
        else
            // Cout status update   
            cout << "Computer is making a move..." << endl;

        takeTurn();
        m_scaffold.display();

        // If both players are bots 
        if (!m_red->isInteractive() && !m_black->isInteractive()) {
            cout << "Press ENTER to continue...";
            cin.ignore(10000, '\n');    // Wait for the user to press enter 
        }
    }

    // Update if someone won and the game is over 
    if (winner == RED)
        cout << m_red->name() << " wins!" << endl;
    else if (winner == BLACK)
        cout << m_black->name() << " wins!" << endl;
    else
        cout << "It's a tie!" << endl;

}

int GameImpl::checkerAt(int c, int r) const
{
    return (m_scaffold.checkerAt(c, r));    // Basically just Scaffold's checkerAt() function again
}

//******************** Game functions **************************************

//  These functions simply delegate to GameImpl's functions.  You should not
//  change any of the code from here to the end of this file.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
