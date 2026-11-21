/**
 * Player.hpp
 */
 
#pragma once

#define _USE_MATH_DEFINES 
 
#include <cmath>

#include "Maze.hpp"

class Player {
public:
	Player(
		DoublePoint &position,
		double fpvWidth
	):
		position_(position),
		fpvWidth_(fpvWidth)
	{
		viewAngleMiddle_ = M_PI / 2;
        	viewAngleStep_ = M_PI / fpvWidth;
		viewAngleSteps_ = fpvWidth;
	}
	
	void turnLeft();
	void turnRight();	
	void stepForward(const Maze &maze);
	void stepBackward(const Maze &maze);

// TODO use getters and setters here
	DoublePoint position_;
	double fpvWidth_;
    	double viewAngleStep_;
    	double viewAngleSteps_;
    	double viewAngleMiddle_;
	static const double viewAngleHalfWidth_;

private:

	static const double turnStep_;
	static const double moveStep_;
	
	void doStep(const Maze &maze, double x, double y);
	
};

