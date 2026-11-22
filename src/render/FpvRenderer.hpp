/**
 * FpvRenderer.hpp
 */
 
#pragma once

#include "Renderer.hpp"
#include "../model/Player.hpp"
#include "../model/Maze.hpp"
#include "../model/Intersection.hpp"

enum class KeyState {
	UP,
	DOWN
};

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
		player_(player),
		forwardState_(KeyState::UP),
		backwardState_(KeyState::UP),
		leftState_(KeyState::UP),
		rightState_(KeyState::UP)
	{
	}
	
protected:
	void handleEvent(SDL_Event *event);
	void updateFrameBuffer();
	
private:
	void drawVerticalLine( double x, Intersection &intersection);
	void setKeyState(SDL_Event *event, KeyState keyState);

	const Maze &maze_;
	Player &player_;
	KeyState forwardState_;
	KeyState backwardState_;
	KeyState leftState_;
	KeyState rightState_;
};
