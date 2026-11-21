/**
 * Renderer.cpp
 */
 
#include "Renderer.hpp"

Renderer::~Renderer() {
	if (texture_) {
        	SDL_DestroyTexture(texture_);
        }
        if (renderer_) {
        	SDL_DestroyRenderer(renderer_);
        }
        if (window_) {
        	SDL_DestroyWindow(window_);
        }
        SDL_Quit();
}

bool Renderer::initialize() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
        	SDL_Log("SDL initialization failed: %s", SDL_GetError());
        	return false;
    	}

    	if (!SDL_CreateWindowAndRenderer(
       		"Pseudo 3D Maze",
       		width_,
       		height_,
       		0,
       	        &window_,
		&renderer_
	)) {
		SDL_Log("Window creation failed: %s", SDL_GetError());
		return false;
	}
    
	texture_ = SDL_CreateTexture(
		renderer_,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		width_,
		height_
	);
	if (texture_ == nullptr) {
    		SDL_Log("Texture creation failed: %s", SDL_GetError());
    		return false;
	}
	return true; 
}

void Renderer::mainLoop() {
	SDL_SetRenderDrawColor(renderer_, 30, 30, 40, 255);
        SDL_RenderClear(renderer_);
//	updateScene(renderer, texture);
	update();
        	    	
    	SDL_Event event;
    	while (true) {
        	while (SDL_PollEvent(&event)) {
        		if (event.type == SDL_EVENT_QUIT) {
                		return;
            		}
        	}
    	}	
}

// TODO invoke FPV rendering here
void Renderer::update() {
	// TODO temporary test
	for (int x=0; x<width_; x++) {
		for (int y=0; y<height_; y++) {
			Pixel pixel{
				(uint8_t) ((x) % 256),
				(uint8_t) ((x + y) % 256),
				(uint8_t) ((y) % 256),
				(uint8_t) 255
			};
			
			frameBuffer_.setPixel(x, y, pixel);
		}	
	}
	
	if (!SDL_UpdateTexture(
    		texture_,
    		nullptr, // all area
	    	frameBuffer_.getPixels().data(),
    		frameBuffer_.getWidth() * sizeof(uint32_t))) 
    	{
    		SDL_Log("Update texture failed: %s", SDL_GetError());
    		return;
    	}
	
	if (!SDL_RenderTexture(renderer_, texture_, nullptr, nullptr)) {
    		SDL_Log("Render texture failed: %s", SDL_GetError());
    		return;		
	}
	
	if (!SDL_RenderPresent(renderer_)) {
    		SDL_Log("Render present failed: %s", SDL_GetError());
	}
	
}

