/**
 * Renderer.hpp
 */
 
#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "PixelBuffer.hpp"

class Renderer {
public:
	Renderer(const std::string &title, int width, int height):
		width_(width),
		height_(height),
		title_(title),
		frameBuffer_(width, height)
	{
	}
		
	virtual ~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;	
	
	bool initialize();
	void mainLoop();
	
protected:
	virtual void handleEvent(SDL_Event *event) = 0;
	virtual void updateFrameBuffer() = 0;
	
	void setPixel(int x, int y, Pixel pixel) {
		frameBuffer_.setPixel(x, y, pixel);
	}	

	const int width_;
	const int height_;
	
private:	
	void render();	
	
	const std::string title_;
	
	PixelBuffer frameBuffer_;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};
