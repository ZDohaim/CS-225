#include "PuzzleAnimation.h"
#include "puzzle.h"

int main(int argc, const char **argv) {

    auto sol = solveAstar(
        PuzzleState({5, 1, 2, 3, 9, 10, 6, 4, 13, 0, 7, 8, 14, 15, 11, 12}),
        PuzzleState({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}));

    PuzzleAnimation ani("<path to image>", sol);
    ani.writeToFile("puzzle.svg");
    return 0;
}
