#include <catch2/catch_test_macros.hpp>
#include <algorithm>

#include "puzzle.h"

TEST_CASE("operator== returns true for equal states", "[weight=1][part=1]")
{
    std::array<uint8_t, 16> state = {
        0, 8, 1, 9,
        2, 10, 3, 11,
        4, 12, 5, 13,
        6, 14, 7, 15};
    PuzzleState puzzle1(state);
    PuzzleState puzzle2(state);

    REQUIRE(puzzle1 == puzzle2);
}

TEST_CASE("operator== returns false for unequal states", "[weight=1][part=1]")
{
    PuzzleState puzzle1({0, 8, 1, 9,
                         2, 10, 3, 11,
                         4, 12, 5, 13,
                         6, 14, 7, 15});

    PuzzleState puzzle2({0, 8, 1, 9,
                         2, 3, 10, 11,
                         4, 12, 5, 13,
                         6, 14, 7, 15});

    REQUIRE(puzzle1 != puzzle2);
}

TEST_CASE("operator< enforces proper ordering", "[weight=1][part=1]")
{
    PuzzleState puzzle1({1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    PuzzleState puzzle2({0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    REQUIRE(puzzle2 < puzzle1);
    REQUIRE(!(puzzle1 < puzzle2));

    PuzzleState solved;
    PuzzleState puzzle3({1, 2, 3, 4, 5, 6, 7, 7, 9, 10, 11, 12, 13, 14, 15, 0});
    PuzzleState puzzle4({1, 2, 3, 4, 5, 6, 7, 9, 9, 10, 11, 12, 13, 14, 15, 0});
    REQUIRE(puzzle3 < solved);
    REQUIRE(solved < puzzle4);
    
    REQUIRE(!(solved < solved));
}

TEST_CASE("Default constructor returns solved puzzle", "[weight=1][part=1]")
{
    PuzzleState solvedPuzzle({1, 2, 3, 4,
                              5, 6, 7, 8,
                              9, 10, 11, 12,
                              13, 14, 15, 0});
    PuzzleState defaultPuzzle;

    REQUIRE(solvedPuzzle == defaultPuzzle);
}

TEST_CASE("getNeighbors returns correct neighbors", "[weight=2][part=1]")
{
    PuzzleState original({1, 2, 3, 4,
                          5, 0, 6, 7,
                          8, 9, 10, 11,
                          12, 13, 14, 15});
    PuzzleState up({1, 0, 3, 4,
                    5, 2, 6, 7,
                    8, 9, 10, 11,
                    12, 13, 14, 15});
    PuzzleState down({1, 2, 3, 4,
                      5, 9, 6, 7,
                      8, 0, 10, 11,
                      12, 13, 14, 15});
    PuzzleState left({1, 2, 3, 4,
                      0, 5, 6, 7,
                      8, 9, 10, 11,
                      12, 13, 14, 15});
    PuzzleState right({1, 2, 3, 4,
                       5, 6, 0, 7,
                       8, 9, 10, 11,
                       12, 13, 14, 15});

    std::vector<PuzzleState> neighbors = original.getNeighbors();
    REQUIRE(neighbors.size() == 4);
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), up) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), down) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), left) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), right) != neighbors.end());
}

TEST_CASE("getNeighbors edge cases", "[weight=2][part=1]")
{
    PuzzleState original({0, 1, 2, 3,
                          4, 5, 6, 7,
                          8, 9, 10, 11,
                          12, 13, 14, 15});

    std::array<uint8_t, 16> expectedState1 = {
        4, 1, 2, 3,
        0, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15};
    std::array<uint8_t, 16> expectedState2 = {
        1, 0, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15};
    std::vector<PuzzleState>
        neighbors = original.getNeighbors();

    REQUIRE(neighbors.size() == 2);

    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState1)) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState2)) != neighbors.end());

    original = PuzzleState();
    expectedState1 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 10, 11, 0,
                      13, 14, 15, 12};
    expectedState2 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 10, 11, 12,
                      13, 14, 0, 15};

    neighbors = original.getNeighbors();
    REQUIRE(neighbors.size() == 2);
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState1)) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState2)) != neighbors.end());

    original = PuzzleState({1, 2, 3, 4,
                            5, 6, 7, 8,
                            9, 10, 11, 0,
                            12, 13, 14, 15});
    expectedState1 = {1, 2, 3, 4,
                      5, 6, 7, 0,
                      9, 10, 11, 8,
                      12, 13, 14, 15};
    expectedState2 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 10, 11, 15,
                      12, 13, 14, 0};
    std::array<uint8_t, 16> expectedState3 = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 0, 11,
        12, 13, 14, 15};
    neighbors = original.getNeighbors();
    REQUIRE(neighbors.size() == 3);
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState1)) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState2)) != neighbors.end());
    REQUIRE(std::find(neighbors.begin(), neighbors.end(), PuzzleState(expectedState3)) != neighbors.end());
}

TEST_CASE("Simple manhattanDistance tests", "[weight=1][part=1]")
{
    PuzzleState solvedPuzzle;
    REQUIRE(solvedPuzzle.manhattanDistance(solvedPuzzle) == 0);

    PuzzleState puzzle({1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12,
                        13, 14, 0, 15});
    REQUIRE(puzzle.manhattanDistance(solvedPuzzle) == 1);

    puzzle = PuzzleState({1, 2, 3, 4,
                          5, 6, 7, 8,
                          9, 10, 0, 12,
                          13, 14, 11, 15});
    REQUIRE(puzzle.manhattanDistance(solvedPuzzle) == 2);

    puzzle = PuzzleState({1, 2, 3, 4,
                          5, 6, 7, 8,
                          9, 10, 0, 15,
                          13, 14, 12, 11});
    REQUIRE(puzzle.manhattanDistance(solvedPuzzle) == 6);
}

TEST_CASE("manhattanDistance using getNeighbor", "[weight=1][part=1]")
{
    PuzzleState start;

    std::vector<PuzzleState::Direction> moves = {PuzzleState::Direction::DOWN, PuzzleState::Direction::RIGHT, PuzzleState::Direction::DOWN, PuzzleState::Direction::LEFT, PuzzleState::Direction::DOWN, PuzzleState::Direction::RIGHT, PuzzleState::Direction::RIGHT, PuzzleState::Direction::UP, PuzzleState::Direction::UP, PuzzleState::Direction::UP, PuzzleState::Direction::RIGHT, PuzzleState::Direction::DOWN, PuzzleState::Direction::DOWN};

    PuzzleState curr = start;
    for (size_t i = 0; i < moves.size(); ++i)
    {
        curr = curr.getNeighbor(moves[i]);
        REQUIRE(curr.manhattanDistance(start) == (int)i + 1);

//         for (size_t i = 0; i < moves.size(); ++i) {
//     curr = curr.getNeighbor(moves[i]);
//     std::cout << "After move " << i << ":";
//     for (auto val : curr.state_) {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;
// }
    }
}

TEST_CASE("Complicated manhattanDistance tests", "[weight=2][part=1]")
{
    PuzzleState solvedPuzzle;
    PuzzleState puzzle({13, 14, 15, 0,
                        1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12});
    REQUIRE(puzzle.manhattanDistance(solvedPuzzle) == 21);

    puzzle = PuzzleState({6, 7, 15, 13,
                          12, 10, 4, 0,
                          3, 5, 14, 1,
                          8, 9, 2, 11});
    REQUIRE(puzzle.manhattanDistance(solvedPuzzle) == 46);

    puzzle = PuzzleState({0, 15, 14, 13,
                          12, 11, 10, 9,
                          8, 7, 6, 5,
                          4, 3, 2, 1});
    REQUIRE(puzzle.manhattanDistance(solvedPuzzle) == 58);
}