/**
 * loadTextures.cpp
 */

#include <cstring>
#include <string> 
#include <format> 
#include <map> 
#include <string_view> 
#include <array> 
#include <vector>
#include <utility>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "loadTextures.hpp"

constexpr std::array<std::string_view, 6> TEXTURE_FILES = {
	"ceiling",
	"floor",
	"wall",
	"window",
	"exitDoor",
	"picture"
};

std::vector<PixelBuffer> storage;

bool loadTexture(const std::string_view textureFileName) {
	// TODO set directory awith textures as subpath of working directory
	const std::string filePath = std::format("/home/oleksandr/personal/c++/pseudo-3d-maze-cpp/textures/{}.png", textureFileName);
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface) {
		SDL_Log("Load image '%s' failed: %s", filePath.c_str(), SDL_GetError());
		return false;
	}
	
	SDL_Surface* rgba = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);	
	if (!rgba) {
		SDL_DestroySurface(surface);
    		SDL_Log("Cannot convert texture: %s", SDL_GetError());
    		return false;
	}	
	
	std::vector<Pixel> pixels(rgba->w * rgba->h);

	if (SDL_LockSurface(rgba)) {
    		const auto* source = static_cast<const uint8_t*>(rgba->pixels);

		for (int y = 0; y < rgba->h; ++y) {
			std::memcpy(
            			pixels.data() + y * rgba->w,
            			source + y * rgba->pitch,
            			rgba->w * sizeof(Pixel)
        		);
    		}
    		SDL_UnlockSurface(rgba);
	} else {
		SDL_DestroySurface(rgba);
		SDL_DestroySurface(surface);
    		SDL_Log("Cannot lock texture: %s", SDL_GetError());
    		return false;			
	}
	
	// Fill pixel bufffer:
	const int width = rgba->w;
	const int height = rgba->h;

	// TODO optimize this	
	PixelBuffer pixelBuffer(width, height);
	for (int y = 0; y<height; y++) {
		for (int x = 0; x<width; x++) {
			Pixel pixel = pixels[y * width + x];
			pixelBuffer.setPixel(x, y, pixel);
		}
	}
	
	storage.push_back(pixelBuffer);
	
	SDL_DestroySurface(rgba);	
	SDL_DestroySurface(surface);
	return true;
}

bool loadTextures() {
	for (const auto name : TEXTURE_FILES) {
		if (name.length()>0) {
			if (!loadTexture(name)) {
				return false;
			}
		}
	}
	return true;	
}

PixelBuffer getTexture(const char *name) {
	std::string_view nameStr(name);
	if (nameStr == "ceiling") {
		return storage[0];	
	}
	if (nameStr == "floor") {
		return storage[1];	
	}
	if (nameStr == "wall") {
		return storage[2];	
	}
	if (nameStr == "window") {
		return storage[3];
	}
	if (nameStr == "exitDoor") {
		return storage[4];
	}
	return storage[5];
	
}

Pixel getPixelFromTexture(const char *name, int x, int y) {
	PixelBuffer buffer = getTexture(name);
	return buffer.getPixel(x, y);
}
