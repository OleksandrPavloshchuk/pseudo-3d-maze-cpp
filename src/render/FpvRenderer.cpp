/**
 * FpvRenderer.cpp
 */
 
#include <cmath>
#include <algorithm>
#include <vector>

#include <iostream>

#include "FpvRenderer.hpp"
#include "../constants.hpp"
#include "../loadTextures.hpp"
#include "../model/MazeCell.hpp"
#include "../model/IntersectionsDetector.hpp"

const double K = 25000;

// TODO temporary until real textures rendering

const Pixel PIXEL_CEILING{204, 255, 255, 255};
const Pixel PIXEL_FLOOR{153, 153, 153, 255};
const Pixel PIXEL_WALL{102, 153, 153, 255};
const Pixel PIXEL_PICTURE{204, 102, 153, 255};
const Pixel PIXEL_WINDOW{204, 204, 255, 255};
const Pixel PIXEL_EXIT_DOOR{255, 255, 204, 255};

const char* getWallTextureName(MazeCellType type) {
	switch(type) {
	case MazeCellType::WALL:
		return "wall";
	case MazeCellType::WINDOW:
		return "window";
	case MazeCellType::PICTURE:
		return "picture";	
	default:
		return "exitDoor";	
	}
}

const int toTexture(double n) {
        return floor(((static_cast<int>(n) % TEXTURE_SIZE) + TEXTURE_SIZE) % TEXTURE_SIZE);
}

const Pixel getWallPixel(
	double y,
	double lineHeight,
	double wallTop,
	Intersection &intersection
) {
        const int textureY = std::min(
            (double) (TEXTURE_SIZE - 1),
            floor((y - wallTop) * TEXTURE_SIZE / lineHeight)
        );
        return getPixelFromTexture(getWallTextureName(intersection.getCell().getType()), intersection.getTextureX(), textureY);
}

/*
    getHorizontalPixel = (
        y: number,
        intersection: Intersection,
        textureType: TextureType
    ): Pixel => {
        // 0.5 - we use center of pixel
        const distance = K / (2 * Math.abs(y + 0.5 - this.imageHeight / 2))

        const worldX = this.playerPosition.x + distance * intersection.dx!
        const worldY = this.playerPosition.y + distance * intersection.dy!

        return getPixelFromTexture(textureType, this.toTexture(worldX), this.toTexture(worldY))
    }
    
*/

const Pixel getFloorPixel(
	double y,
	Intersection &intersection
) { 
//this.getHorizontalPixel(y, intersection, "floor")
	return PIXEL_FLOOR;
}

const Pixel getCeilingPixel(
	double y,
	Intersection &intersection
) { 
// this.getHorizontalPixel(y, intersection, "ceiling")
	return PIXEL_CEILING;	
}

const Pixel getPixel(
        double y,
        double wallTop,
        double wallBottom,
        double lineHeight,
        Intersection &intersection
) {
	if (y < wallTop) {
		return getCeilingPixel(y, intersection);
        } else if (y >= wallBottom) {
		return getFloorPixel(y, intersection);
        } else {
		return getWallPixel(y, lineHeight, wallTop, intersection);
        }
}

void FpvRenderer::drawVerticalLine(
	double x,
	Intersection &intersection
) {
	const double lineHeight = K / intersection.getDistance();
	
	const double wallTop = floor((height_ - lineHeight) / 2);
	const double wallBottom = floor((height_ + lineHeight) / 2);
	
        for (int y = 0; y < height_; y++) {
		const Pixel pixel = getPixel(y, wallTop, wallBottom, lineHeight, intersection);
		setPixel(x, y, pixel);
	}	
}



/*


    getFloorPixel = (
        y: number,
        intersection: Intersection,
    ): Pixel => this.getHorizontalPixel(y, intersection, "floor")

    getCeilingPixel = (
        y: number,
        intersection: Intersection,
    ): Pixel => this.getHorizontalPixel(y, intersection, "ceiling")

    getHorizontalPixel = (
        y: number,
        intersection: Intersection,
        textureType: TextureType
    ): Pixel => {
        // 0.5 - we use center of pixel
        const distance = K / (2 * Math.abs(y + 0.5 - this.imageHeight / 2))

        const worldX = this.playerPosition.x + distance * intersection.dx!
        const worldY = this.playerPosition.y + distance * intersection.dy!

        return getPixelFromTexture(textureType, this.toTexture(worldX), this.toTexture(worldY))
    }

    toTexture = (n: number) =>
        Math.floor(((n % TEXTURE_SIZE) + TEXTURE_SIZE) % TEXTURE_SIZE)

}
*/




void FpvRenderer::updateFrameBuffer() {
	IntersectionsDetector intersectionsDetector(player_, maze_);
	std::vector<Intersection> intersections = intersectionsDetector.calculate();
	
	for (int x = 0; x < width_; x++) {
		const int index = floor(x * intersections.size() / width_);
		drawVerticalLine(x, intersections[index]);
        }	
}

void FpvRenderer::handleEvent(SDL_Event *event) {
	switch (event->type) {
		case SDL_EVENT_KEY_DOWN:
			setKeyState(event, KeyState::DOWN);
			break;
		case SDL_EVENT_KEY_UP:
			setKeyState(event, KeyState::UP);
			break;
	}
}

void FpvRenderer::setKeyState(SDL_Event *event, KeyState state) {
	const bool doMove = state == KeyState::DOWN;
        switch (event->key.key) {
            case SDLK_UP:
            	forwardState_ = state;
            	if (doMove) {
	                player_.stepForward(maze_);
	        }
                break;
            case SDLK_DOWN:
            	backwardState_ = state;
            	if (doMove) {
                	player_.stepBackward(maze_);
                }
                break;
            case SDLK_LEFT:
            	leftState_ = state;
            	if (doMove) {
			player_.turnLeft();
		}
                break;
            case SDLK_RIGHT:
            	rightState_ = state;
            	if (doMove) {
			player_.turnRight();
		}
                break;
        }
}



