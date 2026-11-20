/**
 * Maze.cpp
 */
 
#include "Maze.hpp"

bool Maze::isCollided(const DoublePoint &pos) const {
	for(const auto &c : field_) {
		if (c.isWall() && c.isCollided(pos, gap_)) {
			return true;
		}
	}
	return false;
}
