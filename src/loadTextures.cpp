/**
 * loadTextures.cpp
 */

#include <string> 
#include <format> 
#include <iostream> 
#include <string_view> 
#include <array> 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "loadTextures.hpp"

constexpr std::array<std::string_view, 6> TEXTURE_FILES = {
	"ceiling" /* ,
	"floor",
	"wall",
	"window",
	"exit_door",
	"picture" */
};

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
	
	// TODO

	
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

/*
import type {Pixel} from "../ui/Pixel.ts";
import {MazeCellType} from "../model/MazeCell";

export const TEXTURE_SIZE = 64

export type HorizontalTexture = "floor" | "ceiling"

export type TextureType = HorizontalTexture | MazeCellType

export const prepareTexture = async (
    type: TextureType

) => {

    const url = `/textures/${type}.png`
    const image = new Image()
    image.src = url

    await image.decode()

    const canvas = document.createElement("canvas")
    canvas.width = image.width
    canvas.height = image.height

    const context = canvas.getContext("2d")!
    context.drawImage(image, 0, 0)

    storage.set(type, context.getImageData(0, 0, image.width, image.height))
}

export const getPixelFromTexture = (
    type: TextureType,
    x: number,
    y: number
): Pixel => {
    const pixels = storage.get(type)
    if (!pixels) {
        return NO_TEXTURE
    }

    const index = (y * TEXTURE_SIZE + x) * 4
    return {
        red: pixels.data[index],
        green: pixels.data[index + 1],
        blue: pixels.data[index + 2]
    }
}

const storage: Map<TextureType, ImageData> = new Map()
const NO_TEXTURE = {red: 0, green: 0, blue: 0}
*/
