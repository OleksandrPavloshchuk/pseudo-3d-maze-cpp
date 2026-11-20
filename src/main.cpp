/**
 * main.cpp
 */
 
#include <SDL3/SDL.h>

#include "constants.hpp"
#include "model/Point.hpp"
#include "model/MazeCell.hpp"
#include "model/Intersection.hpp"

int main() {
    	if (!SDL_Init(SDL_INIT_VIDEO)) {
        	SDL_Log("SDL initialization failed: %s", SDL_GetError());
        	return 1;
    	}
    	

    	SDL_Window* window = SDL_CreateWindow(
        	"Pseudo 3D Maze",
        	640,
        	480,
        	0
    	);

    	if (window == nullptr) {
        	SDL_Log("Window creation failed: %s", SDL_GetError());
        	SDL_Quit();
        	return 1;
    	}

    	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    	if (renderer == nullptr) {
        	SDL_Log("Renderer creation failed: %s", SDL_GetError());
        	SDL_DestroyWindow(window);
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
        	SDL_RenderPresent(renderer);
    	}

    	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(window);
    	SDL_Quit();

    	return 0;
}
