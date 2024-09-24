#include <catch2/catch_test_macros.hpp>

#include "PuzzleAnimation.h"
#include "puzzle.h"

void animateSolution(const std::vector<PuzzleState> &solution, std::string filename) {
    PuzzleAnimation animation(solution);
    animation.writeToFile(filename);
}

size_t testBFS(std::vector<PuzzleState>& expected, bool animate = false) {
    size_t iterations;
    std::vector<PuzzleState> solution = solveBFS(expected[0], expected[expected.size() - 1], &iterations);

    if (animate) {
        animateSolution(solution, "solveBFS_output.svg");
        animateSolution(expected, "solveBFS_expected.svg");
    }

    REQUIRE(solution.size() == expected.size());
    for (size_t i = 0; i < solution.size(); ++i) {
        REQUIRE(solution[i] == expected[i]);
    }
    return iterations;
}

size_t testAstar(std::vector<PuzzleState>& expected, bool animate = false) {
    size_t iterations;
    std::vector<PuzzleState> solution = solveAstar(expected[0], expected[expected.size() - 1], &iterations);

    if (animate) {
        animateSolution(solution, "solveAstar_output.svg");
        animateSolution(expected, "solveAstar_expected.svg");
    }

    REQUIRE(solution.size() == expected.size());
    for (size_t i = 0; i < solution.size(); ++i) {
        REQUIRE(solution[i] == expected[i]);
    }

    return iterations;
}



TEST_CASE("BFS: Solve on solved puzzle", "[weight=1][part=2][BFS]") {
    std::vector<PuzzleState> expected = {PuzzleState()};
    testBFS(expected);
}

TEST_CASE("BFS: Easy solve", "[weight=2][part=2][BFS]") {
    std::vector<PuzzleState> expected1 = {PuzzleState({
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 0,  15
        }),
        PuzzleState()
    };
    std::vector<PuzzleState> expected2 = {PuzzleState({
            1,  2,  3,  0,
            5,  6,  7,  4,
            9,  10, 11, 8,
            13, 14, 15, 12
        }), PuzzleState({
            1,  2,  3,  4,
            5,  6,  7,  0,
            9,  10, 11, 8,
            13, 14, 15, 12
        }), PuzzleState({
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 0,
            13, 14, 15, 12
        }),
        PuzzleState()
    };

    testBFS(expected1);
    testBFS(expected2);
}

TEST_CASE("BFS: Spiral test", "[weight=2][part=2][BFS][valgrind][timeout=15000]") {
    std::vector<PuzzleState> expected = {
        PuzzleState({5, 1, 2, 3, 9, 10, 6, 4, 13, 0, 7, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 0, 6, 4, 13, 10, 7, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 0, 4, 13, 10, 7, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 0, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 11, 8, 14, 15, 0, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 11, 8, 14, 0, 15, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 11, 8, 0, 14, 15, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 0, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({5, 1, 2, 3, 0, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({0, 1, 2, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 0, 2, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 0, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 0, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 0, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0})
    };

    testBFS(expected, true);
}

TEST_CASE("BFS: Correct number of iterations", "[weight=1][part=2][BFS]") {
    size_t iterations;
    solveBFS(PuzzleState(), PuzzleState(), &iterations);
    REQUIRE(iterations == 1);

    solveBFS(PuzzleState({
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 0,  15
    }), PuzzleState(), &iterations);
    REQUIRE(iterations >= 2);
    REQUIRE(iterations <= 4);

    solveBFS(PuzzleState({
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 0, 12,
        13, 14, 11, 15
    }), PuzzleState(), &iterations);
    REQUIRE(iterations >= 6);
    REQUIRE(iterations <= 15);
}

TEST_CASE("A*: Solve on solved puzzle", "[weight=1][part=2][A*]") {
    std::vector<PuzzleState> expected = {PuzzleState()};
    testAstar(expected);
}

TEST_CASE("A*: Easy solve", "[weight=2][part=2][A*]") {
    std::vector<PuzzleState> expected1 = {PuzzleState({
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 0,  15
        }),
        PuzzleState()
    };
    std::vector<PuzzleState> expected2 = {PuzzleState({
            1,  2,  3,  0,
            5,  6,  7,  4,
            9,  10, 11, 8,
            13, 14, 15, 12
        }), PuzzleState({
            1,  2,  3,  4,
            5,  6,  7,  0,
            9,  10, 11, 8,
            13, 14, 15, 12
        }), PuzzleState({
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 0,
            13, 14, 15, 12
        }),
        PuzzleState()
    };

    testAstar(expected1);
    testAstar(expected2);
}

TEST_CASE("A*: Spiral test", "[weight=2][part=2][A*][valgrind][timeout=15000]") {
    std::vector<PuzzleState> expected = {
        PuzzleState({5, 1, 2, 3, 9, 10, 6, 4, 13, 0, 7, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 0, 6, 4, 13, 10, 7, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 0, 4, 13, 10, 7, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 0, 8, 14, 15, 11, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 11, 8, 14, 15, 0, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 11, 8, 14, 0, 15, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 13, 10, 11, 8, 0, 14, 15, 12}),
        PuzzleState({5, 1, 2, 3, 9, 6, 7, 4, 0, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({5, 1, 2, 3, 0, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({0, 1, 2, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 0, 2, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 0, 3, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 0, 5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 0, 9, 10, 11, 8, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 13, 14, 15, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0})
    };

    testAstar(expected, true);
}

TEST_CASE("A*: Correct number of iterations", "[weight=1][part=2][A*]") {
    size_t iterations;
    solveAstar(PuzzleState(), PuzzleState(), &iterations);
    REQUIRE(iterations == 1);

    solveAstar(PuzzleState({
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 0,  15
    }), PuzzleState(), &iterations);
    REQUIRE(iterations == 2);

    solveAstar(PuzzleState({
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 0, 12,
        13, 14, 11, 15
    }), PuzzleState(), &iterations);
    REQUIRE(iterations == 3);
}

TEST_CASE("A* much faster than BFS", "[weight=2][part=2][timeout=15000]") {
    size_t iterationsBFS, iterationsAstar;
    solveBFS(PuzzleState({5, 1, 7, 4, 9, 3, 11, 8, 0, 2, 12, 15, 13, 6, 10, 14}), PuzzleState(), &iterationsBFS);
    solveAstar(PuzzleState({5, 1, 7, 4, 9, 3, 11, 8, 0, 2, 12, 15, 13, 6, 10, 14}), PuzzleState(), &iterationsAstar);
    // Note: it is not always possible to know exactly how many iterations A*
    // will take, but it is possible for this particular test case.
    REQUIRE(iterationsAstar == 19);
    REQUIRE(iterationsBFS > 300000);
    REQUIRE(iterationsBFS < 1500000);
}

