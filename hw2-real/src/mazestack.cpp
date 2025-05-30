#include <iostream>
#include <stack>
using namespace std;

class Coord
{
   public:
     Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
     int r() const { return m_r; }
     int c() const { return m_c; }
   private:
     int m_r;
     int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','X','X' },
        { 'X','.','X','X','.','X','X','.','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
	
    if (pathExists(maze, 3, 5, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	stack<Coord> coordStack;
	// Push starting coordinate (sr, sc)
	coordStack.push(Coord(sr, sc));
	// Update maze [sr][sc]
	maze[sr][sc] = '#';

	// While stack is not empty
	while (!coordStack.empty()) {
		// Pop top coordinate off the stack
		Coord p = coordStack.top();
		if (p.r() == er && p.c() == ec) {
			return true;
		}
		// Define r and c
		int r = p.r();
		int c = p.c();
		coordStack.pop();

		cerr << p.r() << p.c() << " ";

		// Check if you can move SOUTH
		if (maze[r + 1][c] == '.') {
			coordStack.push(Coord(r + 1, c));
			maze[r + 1][c] = '#';
		}
		// Check if you can move WEST
		if (maze[r][c - 1] == '.') {
			coordStack.push(Coord(r, c - 1));
			maze[r][c - 1] = '#';
		}
		// Check if you can move NORTH
		if (maze[r - 1][c] == '.') {
			coordStack.push(Coord(r - 1, c));
			maze[r - 1][c] = '#';
		}
		if (maze[r][c + 1] == '.') {
			coordStack.push(Coord(r, c + 1));
			maze[r][c + 1] = '#';
		}
	};
	return false;
}
