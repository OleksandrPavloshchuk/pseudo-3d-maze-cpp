/**
 * MazeCell.cpp
 */
 
#include "../constants.hpp" 
#include "MazeCell.hpp"

bool MazeCell::isCollided(const DoublePoint &pos, double gap) const {
	return (pos.getX() >= center_.getX() - TEXTURE_SIZE / 2 - gap
		&& pos.getX() <= center_.getX() + TEXTURE_SIZE / 2 + gap
		&& pos.getY() >= center_.getY() - TEXTURE_SIZE / 2 - gap
		&& pos.getY() <= center_.getY() + TEXTURE_SIZE / 2 + gap
	);
}

