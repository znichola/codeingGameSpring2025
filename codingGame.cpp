#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef uint8_t Dice; // should be between 0..7, but idk how to type it
typedef vector<Dice> Grid;

typedef uint32_t BoardHash;
typedef vector<BoardHash> Solutions;

typedef uint8_t Pos; // should be between 0..9, but idk how to type it
typedef struct {
   Dice n;
   Dice e;
   Dice s;
   Dice w;
} Neighbours; // limited to 0..4, as above
typedef Neighbours Captures;

enum {
    N = 1,
    E = 1 << 1,
    S = 1 << 2,
    W = 1 << 3,
};
typedef uint8_t CaptureMask;

typedef struct {
    Pos pos;
    Dice dice;
    Captures captures = {11, 11, 11, 11};
} Move;
typedef vector<Move> PossibleMoves;

typedef struct {
    uint8_t current;
    uint8_t max;
}  Depth;

typedef unsigned long long Result;


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
// get_neighbours :: Pos -> Neighbours


         bool is_solved(const Grid &grid);
    BoardHash get_solution(const Grid &grid);
PossibleMoves get_possible_moves(const Grid &grid);
    Solutions check_all_moves(const Grid &grid, const Depth &depth);
   Neighbours get_neighbours(const Pos pos, const Grid &grid);


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

    cerr << "\nOUTPUT" << endl;
    cout << get_result(solutions) << endl;
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

        cout << "NEIGHBOURS" << endl;
        auto neighbours = get_neighbours(i, grid);
        Dice * nn = reinterpret_cast<Dice *>(&neighbours);

        for (uint8_t i = 0; i < 4; i++) {
            cout << static_cast<int>(nn[i]) << ", ";
        }
        cout << endl;

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

Result get_result(const Solutions &solutions) {
    Result final_sum = 0;
    for (const auto &s : solutions) {
        final_sum = (final_sum + static_cast<Result>(s)) % (1 << 30);
    }
    return final_sum;
}

// 0 1 2
// 3 4 5
// 6 7 8

Neighbours get_neighbours(const Pos pos, const Grid &g) {
    switch (pos) {
        case 0 : return {11, g[1], g[3], 11};
        case 1 : return {11, g[2], g[4], g[0]};
        case 2 : return {11, 11, g[5], g[1]};
        case 3 : return {g[0], g[4], g[6], 11};
        case 4 : return {g[1], g[5], g[7], g[3]};
        case 5 : return {g[2], 11, g[8], g[4]};
        case 6 : return {g[3], g[7], 11, 11};
        case 7 : return {g[4], g[8], 11, g[6]};
        case 8 : return {g[5], 11, 11, g[7]};
    }
    throw runtime_error("Pos out of range!");
}

CaptureMask get_cardinals(Pos pos) {
    switch (pos) {
        case 0 : return     E | S    ;
        case 1 : return     E | S | W;
        case 2 : return         S | W;
        case 3 : return N | E | S    ;
        case 4 : return N | E | S | W;
        case 5 : return N |     S | W;
        case 6 : return N | E        ;
        case 7 : return N | E |     W;
        case 8 : return N |         W;
    }
    throw runtime_error("Pos out of range!");
}

