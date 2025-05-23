#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include <string>
#include "provided.h"
using namespace std;

bool helpNInARow(const Scaffold& s, int col, int level, int deltaCol, int deltaLevel, int N, int color);
bool checkGameOver(const Scaffold& s, int N, int& winner);
int makeComputerMove(const Scaffold& s, int N, int color, int depth);
pair<int, int> determineBestComputerMove(Scaffold& s, int N, int color, int depth);
pair<int, int> determineBestHumanMove(Scaffold& s, int N, int color, int depth);

#endif