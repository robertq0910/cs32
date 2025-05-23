#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include <string>
#include "provided.h"
using namespace std;

bool helpNInARow(const Scaffold& s, int col, int level, int deltaCol, int deltaLevel, int N, int color);
bool checkGameOver(const Scaffold& s, int N, int& winner);
int makeComputerMove(Scaffold& s, int N, int color, int depth, int smartColor, int& bestCol, int& winner);
pair<int, int> determineBestComputerMove(Scaffold& s, int N, int color, int depth, int smartColor, int& bestCol, int& winner);
pair<int, int> determineBestHumanMove(Scaffold& s, int N, int color, int depth, int smartColor, int& bestCol, int& winner);

#endif