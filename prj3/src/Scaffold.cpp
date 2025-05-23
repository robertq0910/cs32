// Scaffold.cpp

#include "provided.h"
#include <utility>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    vector<vector<int>> m_grid;
    int m_cols;
    int m_levels;
    stack<pair<int, int>> m_moveHistory;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0) {
        cerr << "Invalid scaffold dimensions" << endl;
        exit(1);
    }

    m_cols = nColumns;
    m_levels = nLevels;

    m_grid.resize(m_cols); // Grid grow has M empty rows
    for (int i = 0; i < m_cols; i++) {
        m_grid[i].resize(m_levels, VACANT);  // Row i now has N colums
    }
    // Now we have an M x N array of colors 

}

int ScaffoldImpl::cols() const
{
    return m_cols;  
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    // Loop through each level and column
    // Check if the cell is VACANT
    int count = 0;
    for (int level = 0; level < m_levels; level++) {
        for (int col = 0; col < m_cols; col++) {
            if (m_grid[col][level] == VACANT) {
                count++;
            }
        }
    }
    // Return number of VACANT cells 
    return count;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{

    return (m_grid[column - 1][level - 1]);
}

void ScaffoldImpl::display() const
{
    // Print rows from top to bottom 
    for (int level = m_levels - 1; level >= 0; level--) {
        // Print one cell per column 
        for (int col = 0; col < m_cols; col++) {
            cout << "|";
            int cell = m_grid[col][level];
            if (cell == RED) {
                cout << "R";
            }
            else if (cell == BLACK) {
                cout << "B";
            }
            else {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    // Bottom bar
    cout << "+";
    for (int col = 0; col < m_cols; col++) {
        cout << "-+";
    }
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    // Check that column paramenter is valid and has >=1 vacant positions
    if (column > m_cols || column < 1 || (color != RED && color != BLACK)) {
        return false;
    }
    // If color = red || black, drop checker into that column, return true
    int colIndex = column - 1;  // Bc the "column" passed in is 1-based
    for (int level = 0; level < m_levels; level++) {
        if (m_grid[colIndex][level] == VACANT) {
            m_grid[colIndex][level] = color;   // Place checker
            m_moveHistory.push({ colIndex, level });    // Push position to checker so we can pop it later to undo
            return true;
        }
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    // If there are no checkers in the scaffold, return 0
    if (m_moveHistory.empty()) {
        return 0;
    }
    // Clear most recent move
    int col = m_moveHistory.top().first;
    int level = m_moveHistory.top().second;
    m_grid[col][level] = VACANT;
    // Undo most recent move
    m_moveHistory.pop();

    // Return column number of removed checker
    return col + 1; // 1-based column number
    
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.  You should
//  not change any of the code from here to the end of this file.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}

Scaffold::~Scaffold()
{
    delete m_impl;
}

Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}

Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}

int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}

void Scaffold::display() const
{
    m_impl->display();
}

bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}

int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
