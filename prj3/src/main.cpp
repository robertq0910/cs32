#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to close this window . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

int main()
{
	SmartPlayer bp("Homer");
	HumanPlayer hp("Marge");
	Game g(4, 4, 3, &bp, &hp);
	g.play();
}