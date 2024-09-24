/**
 * @file PuzzleAnimation.h
 */

#pragma once

#include "puzzle.h"

#include <array>
#include <cstdint>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

/**
 * Puzzle animation utility class
 */
class PuzzleAnimation {
  public:
    /**
     * Constructs an animated puzzle with numeric board.
     * @param transitions same as the results from solveAstar/solveBFS
     */
    PuzzleAnimation(std::vector<PuzzleState> const &transitions)
        : transitions_(transitions) {}

    /**
     * Constructs an animated puzzle with an image board.
     * @param img_path path the image used for animation
     * @param transitions same as the results from solveAstar/solveBFS
     */
    PuzzleAnimation(std::string const &img_path,
                    std::vector<PuzzleState> const &transitions)
        : transitions_(transitions), img_path_(img_path) {}

    /**
     * Writes the animation to an SVG file, you can open any modern browser,
     * or use an SVG VSCode extension to view the SVG.
     * @param fname name of the file
     */
    void writeToFile(std::string fname);

    /** width of the svg */
    double width = 200;
    /** height of the svg */
    double height = 200;
    /** size of each tile */
    double tileSize = std::min(width, height) / 4;
    /** duration of each animation step in seconds */
    double stepDuration = 0.3;

  private:
    std::array<std::stringstream, 16> createAnimationTags(
        std::array<uint8_t, 16> const &initialState,
        std::vector<int> const &directions,
        std::function<double(int)> offsetX = [](int) { return 0; },
        std::function<double(int)> offsetY = [](int) { return 0; });

    bool isValid(int pos, int dir);
    std::vector<PuzzleState> transitions_;
    std::string img_path_;
};
