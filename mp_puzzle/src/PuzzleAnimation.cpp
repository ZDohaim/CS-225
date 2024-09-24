#include "PuzzleAnimation.h"

#include <algorithm>
#include <cassert>
#include <fstream>

static std::array<int, 4> offsets = {1, 4, -1, -4};

void PuzzleAnimation::writeToFile(std::string fname) {
    std::array<uint8_t, 16> initialState = transitions_[0].asArray();
    std::array<uint8_t, 16> board = initialState;

    // 0: → 1: ↓ 2: ← 3: ↑
    // this is actually the direction moved by the empty space on the puzzle
    std::vector<int> directions;

    for (size_t i = 0; i < transitions_.size() - 1; i++) {
        auto s1 = transitions_[i];
        auto s2 = transitions_[i + 1];
        auto a1 = s1.asArray();
        auto a2 = s2.asArray();
        auto pos1 = std::find(a1.begin(), a1.end(), 0) - a1.begin();
        auto pos2 = std::find(a2.begin(), a2.end(), 0) - a2.begin();
        auto dir = std::find(offsets.begin(), offsets.end(), pos2 - pos1) -
                   offsets.begin();
        directions.push_back(dir);
    }

    if (fname.substr(fname.length() - 4, 4) != ".svg")
        fname += ".svg";
    std::ofstream f(fname);

    f << "<svg width=\"" << width << "\" height=\"" << height
      << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

    if (!img_path_.size()) {
        auto textOffset = [=](int) { return tileSize / 2; };
        std::array<std::stringstream, 16> textAnimationTags =
            createAnimationTags(initialState, directions, textOffset,
                                textOffset);
        std::array<std::stringstream, 16> rectAnimationTags =
            createAnimationTags(initialState, directions);

        f << "<rect x=\"0\" y=\"0\" width=\"" << width << "\" height=\""
          << height << "\" style =\"fill:gray;\"/>" << std::endl;
        f << "<style>rect{fill:white;stroke:black;stroke-width:2;}text{"
             "text-anchor:middle;font-family:monospace;dominant-baseline:"
             "middle;}</style>"
          << std::endl;

        for (int i = 0; i < 16; i++) {
            int tile = initialState[i];
            if (tile == 0)
                continue;
            int pos = i;
            int x = pos % 4;
            int y = pos / 4;
            f << "<rect x=\"" << x * tileSize << "\" y=\"" << y * tileSize
              << "\" width=\"" << tileSize << "\" height=\"" << tileSize
              << "\">" << std::endl;
            f << rectAnimationTags[tile].str();
            f << "</rect>" << std::endl;

            f << "<text x=\"" << x * tileSize + tileSize / 2 << "\" y=\""
              << y * tileSize + tileSize / 2 << "\" font-size=\""
              << std::min(width, height) / 10 << "\">" << tile << std::endl;
            f << textAnimationTags[tile].str();
            f << "</text>" << std::endl;
        }
    } else {
        auto imgOffsetX = [=](int pos) {
            return -(((pos - 1) % 4) * tileSize);
        };
        auto imgOffsetY = [=](int pos) {
            return -((int)((pos - 1) / 4) * tileSize);
        };

        std::array<std::stringstream, 16> maskAnimationTags =
            createAnimationTags(initialState, directions);
        std::array<std::stringstream, 16> imgAnimationTags =
            createAnimationTags(initialState, directions, imgOffsetX,
                                imgOffsetY);
        f << "<rect x=\"0\" y=\"0\" width=\"" << width << "\" height=\""
          << height << "\" style =\"fill:white;\"/>" << std::endl;
        for (int i = 0; i < 16; i++) {
            int tile = initialState[i];
            if (tile == 0)
                continue;

            int pos = i;
            int x = pos % 4;
            int y = pos / 4;
            f << "<mask id=\"mask-" << tile << "\"><rect x=\"" << x * tileSize
              << "\" y=\"" << y * tileSize << "\" width=\"" << tileSize
              << "\" height=\"" << tileSize << "\" fill=\"white\">"
              << std::endl;
            f << maskAnimationTags[tile].str();
            f << "</rect></mask>" << std::endl;

            f << "<image x=\"" << x * tileSize + imgOffsetX(tile) << "\" y=\""
              << y * tileSize + imgOffsetY(tile) << "\" width=\"" << width
              << "\" height=\"" << height << "\" href=\"" << img_path_
              << "\" mask=\"url(#mask-" << tile << ")\">" << std::endl;
            f << imgAnimationTags[tile].str();
            f << "</image>" << std::endl;
        }
    }
    f << "</svg>";
}

std::array<std::stringstream, 16> PuzzleAnimation::createAnimationTags(
    std::array<uint8_t, 16> const &initialState,
    std::vector<int> const &directions, std::function<double(int)> offsetX,
    std::function<double(int)> offsetY) {

    std::array<uint8_t, 16> board = initialState;
    std::array<int, 16> positions;
    std::array<std::stringstream, 16> out;

    for (int i = 0; i < 16; i++) {
        positions[initialState[i]] = i;
    }

    auto it0 = std::find(initialState.begin(), initialState.end(), 0);
    // must be a zero on board
    assert(it0 != initialState.end());
    int pos0 = it0 - initialState.begin();

    int i = 0;
    for (int dir : directions) {
        // moves must be valid
        assert(isValid(pos0, dir));

        int tileToMove = board[pos0 + offsets[dir]];
        int originalPos = positions[tileToMove];
        int originalX = originalPos % 4;
        int originalY = originalPos / 4;
        int newPos = originalPos + offsets[(dir + 2) % 4];
        int newX = newPos % 4;
        int newY = newPos / 4;
        double offX = offsetX(tileToMove);
        double offY = offsetY(tileToMove);

        std::string axis = dir % 2 ? "y" : "x";
        if ((dir % 2)) {
            std::swap(originalX, originalY);
            std::swap(newX, newY);
            std::swap(offX, offY);
        }

        out[tileToMove] << "<animate attributeName=\"" << axis << "\" from=\""
                        << originalX * tileSize + offX << "\" to=\""
                        << newX * tileSize + offX << "\" begin=\""
                        << i * stepDuration << "s\" dur=\"" << stepDuration
                        << "s\" fill=\"freeze\" />" << std::endl;

        std::swap(board[pos0], board[positions[tileToMove]]);
        positions[tileToMove] = newPos;
        pos0 += offsets[dir];
        i++;
    }

    return out;
}

bool PuzzleAnimation::isValid(int pos, int dir) {
    return (dir == 0 && pos % 4 != 3) || (dir == 1 && pos < 12) ||
           (dir == 2 && pos % 4 != 0) || (dir == 3 && pos > 3);
}
