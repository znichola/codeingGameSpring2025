#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef uint8_t Dice;
typedef vector<Dice> Grid;

typedef uint32_t BoardHash;
typedef vector<BoardHash> Solutions;

typedef uint8_t Pos;
typedef struct {
    Pos pos;
    Dice dice;
} Move;
typedef vector<Move> PossibleMoves;

typedef struct {
    uint8_t current;
    uint8_t max;
}  Depth;

ostream& operator<<(ostream &os, const Dice &dice) {
    os << static_cast<int>(dice);
    return os;
}

ostream& operator<<(ostream &os, const Grid &grid) {
    for (int i = 0; i < 9; i++) {
        os << grid[i];
        if ((i + 1) % 3 == 0) os << '\n';
        else os << ' ';
    }
    return os;
}

ostream& operator<<(ostream &os, const Move &move) {
    return os << '[' << move.pos << ' ' << move.dice << "] ";
}

ostream& operator<<(ostream &os, const Solutions &solutions) {
    os << '[';
    for (const auto & s : solutions)
        os << s << ", ";
    os << ']';
    return os;
}

ostream& operator<<(ostream &os, const PossibleMoves &pm) {
    for (const auto & p : pm)
        os << p;
    return os;
}


// is_solved :: Grid -> Boolean
// get_solution :: Grid -> BoardHash
// get_possible_moves :: Grid -> PossibleMoves
// do_move :: (Grid Move) -> Grid
// check_all_moves :: (Grid Depth Solutions) -> Solutions


bool is_solved(const Grid &grid);
void add_to_solve(const Grid &grid, Solutions &solutions);
BoardHash get_solution(const Grid &grid);
PossibleMoves get_possible_moves(const Grid &grid);
Solutions check_all_moves(const Grid &grid, const Depth &depth);

unsigned long long get_result(const Solutions &solutions);

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
    auto solutions = check_all_moves(grid, {0, static_cast<uint8_t>(depth)});
    cerr << "CHECK ALL MOVES\n" << solutions << endl;



    cerr << "OUTPUT" << endl;
    cout << get_result(solutions) << endl;
    cerr << "322444322" << endl;
    // cout << "0" << endl;
}

bool is_solved(const Grid &grid) {
    for (const auto &c : grid)
        if (c == 0) return false;
    return true;
}

BoardHash get_solution(const Grid &grid) {
    return grid[0] * 100000000 +
           grid[1] * 10000000 +
           grid[2] * 1000000 +
           grid[3] * 100000 +
           grid[4] * 10000 +
           grid[5] * 1000 +
           grid[6] * 100 +
           grid[7] * 10 +
           grid[8];
}

PossibleMoves get_possible_moves(const Grid &grid) {
    PossibleMoves pm;
    for (Pos i = 0; i < 9; i++) {
        if (grid[i] == 0) pm.push_back({i, 1});
    }
    // expand with more filler moves - it gets complicated here
    return pm;
}

Grid do_move(const Grid &grid, const Move &move) {
    auto newGrid = grid;
    newGrid[move.pos] = move.dice;
    return newGrid;
}

Solutions check_all_moves(const Grid &grid, const Depth &depth) {
    if (is_solved(grid) || depth.current >= depth.max)
        return {get_solution(grid)};

    Solutions solutions;

    auto possibleMoves = get_possible_moves(grid);

    for (const auto & move : possibleMoves) {
        auto newGrid = do_move(grid, move);
        auto newSolutions = check_all_moves(newGrid
                ,{static_cast<uint8_t>(depth.current + 1), depth.max});

        if (newSolutions.size() != 0)
            solutions.insert(solutions.end()
                            ,newSolutions.begin()
                            ,newSolutions.end()
                            );
    }
    return solutions;
}

unsigned long long get_result(const Solutions &solutions) {
    unsigned long long final_sum = 0;
    for (const auto &s : solutions) {
        final_sum = (final_sum + static_cast<unsigned long long>(s)) % (1 << 30);
    }
    return final_sum;
}

