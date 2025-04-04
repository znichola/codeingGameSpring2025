#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef vector<uint8_t> Line;
typedef vector<Line> Grid;

typedef uint32_t BoardHash;
typedef vector<BoardHash> Solutions;

ostream& operator<<(ostream& os, const Grid& grid) {
    for (const Line& line : grid) {
        for (size_t i = 0; i < line.size(); ++i) {
            os << line[i];
            if (i != line.size() - 1) {
                os << " ";
            }
        }
        os << '\n';
    }
    return os;
}


// is_solved :: Grid -> Boolean
// add_to_solve :: (Solutions Grid) -> Solutions
// get_possible_moves :: Grid -> PossibleMoves
// check_all_moves :: (Grid Depth Solutions) -> Solutions


void add_to_solve(const Grid &grid, Solutions &solutions);


// there is a board with a certain number of free moves, I need to explore all
// posibilites of doing these moves. so backtracking and later some optimization.
// I dont care who goes first, just to itterate over all the possible combinations

int main()
{
    int depth;
    Grid grid;
    cin >> depth; cin.ignore();
    for (int i = 0; i < 3; i++) {
        Line line;
        for (int j = 0; j < 3; j++) {
            int8_t value;
            cin >> value; cin.ignore();
            line.push_back(value);
        }
        grid.push_back(line);
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
    for (const auto line : grid) {
        for (const auto c: line) {
            if (c == 0) return false;
        }
    }
    return true;
}

void add_to_solve(const Grid &grid, Solutions &solutions) {
    int number = grid[0][0] * 100000000 +
                 grid[0][1] * 10000000 +
                 grid[0][2] * 1000000 +
                 grid[1][0] * 100000 +
                 grid[1][1] * 10000 +
                 grid[1][2] * 1000 +
                 grid[2][0] * 100 +
                 grid[2][1] * 10 +
                 grid[2][2];

    cout < grid[0][0] << endl;
    cout << static_cast<int>(grid[0][0]) * 100000000 << endl;
    solutions.push_back(number);
}


