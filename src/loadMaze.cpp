/**
 * loadMaze.cpp
 */
 
#include "loadMaze.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

MazeCellType getType(char src) {
    switch (src) {
        case '#':
            return MazeCellType::WALL;
        case 'E':
            return MazeCellType::EXIT_DOOR;
        case 'P':
            return MazeCellType::PICTURE;
        case 'O':
            return MazeCellType::WINDOW;
        default:
            return MazeCellType::EMPTY;
    }
}

Maze loadMaze(const std::string& mazeResource, double playerWallGap) {
    std::ifstream file(mazeResource);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open maze file: " + mazeResource);
    }

    std::vector<MazeCell> field;
    std::string row;

    int y = 0;

    while (std::getline(file, row)) {
        for (int x = 0; x < static_cast<int>(row.size()); x++) {
            field.emplace_back(
                IntPoint(x, y),
                DoublePoint(
                    (x + 0.5) * TEXTURE_SIZE,
                    (y + 0.5) * TEXTURE_SIZE
                ),
                getType(row[x])
            );
        }

        y++;
    }

    return Maze(std::move(field), playerWallGap);
}
