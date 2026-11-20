/**
 * MazeCell.cpp
 */
 
#include "MazeCell.hpp"

bool MazeCell::isCollided(const DoublePoint &pos, double gap) const {
	return (pos.getX() >= center_.getX() - TEXTURE_SIZE / 2 - gap
		&& pos.getX() <= center_.getX() + TEXTURE_SIZE / 2 + gap
		&& pos.getY() >= center_.getY() - TEXTURE_SIZE / 2 - gap
		&& pos.getY() <= center_.getY() + TEXTURE_SIZE / 2 + gap
	);
}

bool MazeCell::isOnEdge(const DoublePoint &p) const {
        if (p.getY() == y0() || p.getY() == y1()) {
        	return p.getX() >= x0() && p.getX() <= x1();
        }
        if (p.getX() == x0() || p.getX() == x1()) {
        	return p.getY() >= y0() && p.getY() <= y1();
        }
        return false;
}
