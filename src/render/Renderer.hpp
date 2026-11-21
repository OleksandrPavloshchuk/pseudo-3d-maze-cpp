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
		
	virtual ~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;	
	
	bool initialize();
	void mainLoop();
	
protected:
	virtual void updateFrameBuffer() = 0;
	
	void setPixel(int x, int y, Pixel pixel) {
		frameBuffer_.setPixel(x, y, pixel);
	}	

	const int width_;
	const int height_;
	
private:	
	void render();	
	
	FrameBuffer frameBuffer_;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};
