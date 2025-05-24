#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include <string>
#include "provided.h"
#include <chrono>
using namespace std;

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff =
            std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
private:
    std::chrono::high_resolution_clock::time_point m_time;
};

// Advance jumpy timer only after jumpInterval calls to elapsed
class JumpyTimer
{
public:
	JumpyTimer(int jumpInterval);
    double elapsed();
    double actualElapsed();
private:
	Timer m_timer;
	int m_jumpInterval;
	int m_callsMade;
	int m_lastElapsed;
};

bool helpNInARow(const Scaffold& s, int col, int level, int deltaCol, int deltaLevel, int N, int color);
bool checkGameOver(const Scaffold& s, int N, int& winner);
int makeComputerMove(const Scaffold& s, int N, int color, int depth, double timeLimit, JumpyTimer& timer);
pair<int, int> determineBestComputerMove(Scaffold& s, int N, int color, int depth, double timeLimit, JumpyTimer& timer);
pair<int, int> determineBestHumanMove(Scaffold& s, int N, int color, int depth, double timeLimit, JumpyTimer& timer);

#endif