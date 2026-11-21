/**
 * Renderer.hpp
 */
 
#pragma once

#include <SDL3/SDL.h>

#include "FrameBuffer.hpp"

class Renderer {
public:
	Renderer(int width, int height):
		width_(width),
		height_(height),
		frameBuffer_(FrameBuffer(width, height))
	{
	}
		
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;	
	
	bool initialize();
	void mainLoop();

private:
	void update();

	int width_;
	int height_;
	FrameBuffer frameBuffer_;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};
