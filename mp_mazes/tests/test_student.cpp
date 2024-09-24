#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"
#include "mazereader.h"

#define READ_SOLUTION_PNG(func, width, height)  \
    read_solution(string("../data/") + func + string("-expected.png"), width, height)
#define READ_UNSOLVED_PNG(func, width, height)  \
    read_unsolved(string("../data/") + func + string("-expected.png"), width, height)
#define READ_SOLUTION_MAZE(func, width, height)  \
    MazeReader(READ_SOLUTION_PNG(func, width, height))
#define READ_UNSOLVED_MAZE(func, widht, height)  \
    MazeReader(READ_UNSOLVED_PNG(func, width, height))

    void assert_maze_acyclic(SquareMaze & maze, int width, int height);
void assert_maze_connected(SquareMaze & maze, int width, int height);
void assert_maze_tree(SquareMaze & maze, int width, int height);
void copyMaze(const MazeReader & source, SquareMaze * dest);
void advancePosition(int * x, int * y, int dir);
PNG read_solution(const string & filename, int width, int height);
PNG read_unsolved(const string & filename, int width, int height);

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
   cs225::PNG solnImage = READ_SOLUTION_PNG("testDrawSolutionMed", 5, 5);
    MazeReader soln(solnImage);
    SquareMaze maze;
    copyMaze(soln, &maze);
    maze.solveMaze();
    PNG * actualOutput = maze.drawMazeWithSolution();
    actualOutput->writeToFile("testDrawSolutionMed" + string("-actual.png"));
    REQUIRE(*actualOutput == solnImage);
    delete actualOutput;
}
