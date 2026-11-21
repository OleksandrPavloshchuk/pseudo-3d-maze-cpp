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
       		title_.c_str(),
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
	render();
        	    	
    	SDL_Event event;
    	while (true) {
        	while (SDL_PollEvent(&event)) {
        		if (event.type == SDL_EVENT_QUIT) {
                		return;
            		}
        	}
    	}	
}

void Renderer::render() {
	updateFrameBuffer();	

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

