/**
 * loadMaze.hpp
 */
 
#pragma once

#include <string>

#include "model/MazeCell.hpp"
#include "model/Maze.hpp"

Maze loadMaze(const std::string& mazeResource, double playerWallGap);
