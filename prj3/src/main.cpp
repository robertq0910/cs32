// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	/*
	string name;
	cout << "What's your name?  ";
	getline(cin, name);
	HumanPlayer hp(name);
	SmartPlayer sp("Computer");
	Game g1(4, 3, 3, &hp, &sp);
	g1.play();
	cout << endl << "This time I'll go first." << endl;
	Game g2(4, 3, 3, &sp, &hp);
	g2.play();
	*/

	//Testing Scaffold.cpp
	Scaffold s(4, 3);
	cout << "Initial empty board" << endl;
	s.display();
	BadPlayer bp("Bot");
	int move = bp.chooseMove(s, 1, RED);
	s.makeMove(move, RED);
	HumanPlayer hp("Olivia");
	int humanMove = hp.chooseMove(s, 1 , BLACK);
	s.makeMove(humanMove, BLACK);
	s.display();

	/*s.makeMove(2, RED);
	s.makeMove(1, BLACK);
	s.makeMove(1, RED);
	cout << "Sorta filling in board" << endl;
	s.display();*/
}
