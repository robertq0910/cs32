// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include "support.h"
using namespace std;

class HumanPlayerImpl
{
public:
    HumanPlayerImpl(HumanPlayer* p);
    int chooseMove(const Scaffold& s, int N, int color);
    //bool isInteractive() const override { return true; }
private:
    // HumanPlayer* m_player;
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

HumanPlayerImpl::HumanPlayerImpl(HumanPlayer* p)
{}

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int col = 0;
    while (true) {
        cout << "Pick a column: ";
        cin >> col;

        if (col < 1 || col > s.cols()) {
            cout << "Column out of range, try again." << endl;
            continue;
        }

        // Check that the top level has empty spaces left
        int topLevel = s.levels();
        if (s.checkerAt(col, topLevel) == VACANT) 
            return col;
    }
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    for (int col = 1; col <= s.cols(); col++) { // Columns are 1-based
            if (s.checkerAt(col, s.levels()) == VACANT) {
                return col;
        }
    }
    return 0;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{ 
    double timeLimit = 9900;
    JumpyTimer timer(1000);

    int bestMove = makeComputerMove(s, N, color, 0, timeLimit, timer);
    // cout << bestMove;
    return bestMove;
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.  You should
//  not change any of the code from here to the end of this file.

HumanPlayer::HumanPlayer(string nm)
    : Player(nm)
{
    m_impl = new HumanPlayerImpl(this);
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
    : Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
    : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
