/**
 * FpvRenderer.hpp
 */
 
#pragma once

#include "Renderer.hpp"
#include "../model/Player.hpp"
#include "../model/Maze.hpp"
#include "../model/Intersection.hpp"

class FpvRenderer : public Renderer {
public:
	FpvRenderer(
		int width, 
		int height,
		const Maze &maze,
		Player &player
	):
		Renderer("Pseudo 3D Maze (2)", width, height),
		maze_(maze),
		player_(player)
	{
	}
	
protected:
	void updateFrameBuffer();
	
private:
	void drawVerticalLine( double x, Intersection &intersection);

	const Maze &maze_;
	Player &player_;
};
