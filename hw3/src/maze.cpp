#include <iostream>
#include <string>
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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    /*
    If the start location is equal to the ending location, then we've solved the maze, so return true.
    Mark the start location as visited.
    For each of the four directions,
        If the location one step in that direction (from the start location)
                has no wall and is unvisited,
            then if calling pathExists starting from that location (and
                        ending at the same ending location as in the current
                        call) returns true,
                     then return true.
    Return false.
    */
    if (sr == er && sc == ec) {
        maze[sr][sc] = '#';
        return true;
    }
    // Go south
    if (maze[sr][sc] == '.') {
        return pathExists(maze, sr + 1, sc, er, ec);
    }
    // Go west
    if (maze[sr][sc] == '.') {
        return pathExists(maze, sr, sc - 1, er, ec);
    }
    // Go north
    if (maze[sr][sc] == '.') {
        return pathExists(maze, sr - 1, sc, er, ec);
    }
    // Go east
    if (maze[sr][sc] == '.') {
        return pathExists(maze, sr, sc + 1, er, ec);
    }
}

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

