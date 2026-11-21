/**
 * IntersectionsDetector.hpp
 */
 
#pragma once

#include <vector>

#include "Player.hpp"
#include "Intersection.hpp"
#include "Maze.hpp"

class IntersectionsDetector {
public:
	IntersectionsDetector(
		const Player &player,
		const Maze &maze
	):
		player_(player),
		maze_(maze)
	{
	}
	
	std::vector<Intersection> calculate();

private:

    	double distance(const DoublePoint &p);
        
	const Player player_;
	const Maze maze_;

};
