#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef uint8_t Cell;
typedef vector<Cell> Grid;

typedef uint32_t BoardHash;
typedef vector<BoardHash> Solutions;

ostream& operator<<(ostream& os, const Cell cell) {
    os << static_cast<int>(cell);
    return os;
}

ostream& operator<<(ostream& os, const Grid& grid) {
    for (int i = 0; i < 9; i++) {
        os << grid[i];
        if ((i + 1) % 3 == 0) os << '\n';
        else os << ' ';
    }
    return os;
}


// is_solved :: Grid -> Boolean
// add_to_solve :: (Solutions Grid) -> Solutions
// get_possible_moves :: Grid -> PossibleMoves
// check_all_moves :: (Grid Depth Solutions) -> Solutions


bool is_solved(const Grid &grid);
void add_to_solve(const Grid &grid, Solutions &solutions);


// there is a board with a certain number of free moves, I need to explore all
// posibilites of doing these moves. so backtracking and later some optimization.
// I dont care who goes first, just to itterate over all the possible combinations

int main()
{
    int depth;
    Grid grid;
    cin >> depth; cin.ignore();
    for (int i = 0; i < 9; i++) {
        int value;
        cin >> value; cin.ignore();
        grid.push_back(value);
    }


    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cerr << "DEPTH " << depth << endl;
    cerr << "GRID\n" << grid << endl;
    Solutions s;
    add_to_solve(grid, s);
    cerr << "HASH " << s[0] << endl;


    cerr << "OUTPUT" << endl;
    cout << "0" << endl;
}

bool is_solved(const Grid &grid) {
    for (const auto &c : grid)
        if (c == 0) return false;
    return true;
}

void add_to_solve(const Grid &grid, Solutions &solutions) {
    int number = grid[0] * 100000000 +
                 grid[1] * 10000000 +
                 grid[2] * 1000000 +
                 grid[3] * 100000 +
                 grid[4] * 10000 +
                 grid[5] * 1000 +
                 grid[6] * 100 +
                 grid[7] * 10 +
                 grid[8];

    solutions.push_back(number);
}


