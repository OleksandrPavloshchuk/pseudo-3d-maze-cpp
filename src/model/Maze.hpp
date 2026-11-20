/**
 * Maze.hpp
 */
 
#pragma once

#include <vector>
#include "MazeCell.hpp"

class Maze {
public:
	Maze(
		const std::vector<MazeCell> &field,
		double gap
	):
		field_(field),
		gap_(gap)
	{
	}
	
	std::vector<MazeCell> getField() const { return field_; }
	double getGap() const { return gap_; }
	
	bool isCollided(const DoublePoint &pos) const;
	
private:
	const std::vector<MazeCell> field_;
	const double gap_;
};
