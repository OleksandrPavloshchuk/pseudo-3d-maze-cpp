/**
 * main.cpp
 */
 
#include <SDL3/SDL.h>

#include "constants.hpp"
#include "loadMaze.hpp"
#include "model/Point.hpp"
#include "model/MazeCell.hpp"
#include "model/Intersection.hpp"
#include "model/IntersectionsDetector.hpp"
#include "model/Maze.hpp"

#include "render/FrameBuffer.hpp"

// Global variables
const int playerWallGap = 6;

const int fpvWidth = 800;
const int fpvHeight = 640;

void updateScene(SDL_Renderer*& renderer, SDL_Texture*& texture) {
	
	FrameBuffer frameBuffer(fpvWidth, fpvHeight);
	
	// TODO temporary test
	for (int x=0; x<fpvWidth; x++) {
		for (int y=0; y<fpvHeight; y++) {
			uint8_t r = x % 256;
			uint8_t g = y % 256;
			uint8_t b = 128;
			uint8_t a = 255;

			uint32_t color =
				r |
				(g << 8) |
				(b << 16) |
				(a << 24);
			frameBuffer.setPixel(x, y, color);
		}	
	}
	
	if (!SDL_UpdateTexture(
    		texture,
    		nullptr, // all area
	    	frameBuffer.getPixels().data(),
    		frameBuffer.getWidth() * sizeof(uint32_t))) 
    	{
    		SDL_Log("Update texture failed: %s", SDL_GetError());
    		return;
    	}
	
	if (!SDL_RenderTexture(renderer, texture, nullptr, nullptr)) {
    		SDL_Log("Render texture failed: %s", SDL_GetError());
    		return;		
	}
	
	if (!SDL_RenderPresent(renderer)) {
    		SDL_Log("Render present failed: %s", SDL_GetError());
	}
				
}

bool initialize(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& texture) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
        	SDL_Log("SDL initialization failed: %s", SDL_GetError());
        	return false;
    	}

    	if (!SDL_CreateWindowAndRenderer(
       		"Pseudo 3D Maze",
       		fpvWidth,
       		fpvHeight,
       		0,
       	        &window,
		&renderer
	)) {
		SDL_Log("Window creation failed: %s", SDL_GetError());
		return false;
	}
    
	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		fpvWidth,
		fpvHeight
	);
	if (texture == nullptr) {
    		SDL_Log("Texture creation failed: %s", SDL_GetError());
    		return false;
	}    
    
    	updateScene(renderer, texture);

	return true;
}


// Entry point
int main() {
    	const Maze maze = loadMaze(
        	"/home/oleksandr/personal/c++/pseudo-3d-maze-cpp/mazes/3.txt",
        	playerWallGap
    	);

    	const DoublePoint startPos(
        	TEXTURE_SIZE * 1.5,
        	TEXTURE_SIZE * 1.5
    	);

    	const Player player(startPos, fpvWidth);

    	SDL_Window* window = nullptr;
    	SDL_Renderer* renderer = nullptr;
    	SDL_Texture* texture = nullptr;
    
    	if (!initialize(window, renderer, texture)) {
        	SDL_Quit();
        	return 1;
    	}

    	bool running = true;
    	SDL_Event event;

    	while (running) {
        	while (SDL_PollEvent(&event)) {
        		if (event.type == SDL_EVENT_QUIT) {
                		running = false;
            		}
        	}
        	SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        	SDL_RenderClear(renderer);
        	
        	updateScene(renderer, texture);
        	
        	SDL_RenderPresent(renderer);
    	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
