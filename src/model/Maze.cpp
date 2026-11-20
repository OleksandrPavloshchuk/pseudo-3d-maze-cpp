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

/*

    isCollided = (pos: Point): boolean => {
        for (const cell of this.field) {
            if (cell.isWall() && cell.isCollided(pos, this.gap)) {
                return true
            }
        }
        return false
    }
}
*/
