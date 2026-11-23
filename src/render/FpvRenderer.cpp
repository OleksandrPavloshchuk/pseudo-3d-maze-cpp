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

// const double K = 30000;

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

int toTexture(double n) {
    	return static_cast<int>(floor(fmod(n, TEXTURE_SIZE) + TEXTURE_SIZE)) % TEXTURE_SIZE;
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

const Pixel FpvRenderer::getHorizontalPixel(
        double y,
        Intersection &intersection,
        const char *texture
) {
        // 0.5 - we use center of pixel
        const double distance = k_ / (2.0 * std::abs(y + 0.5 - height_ / 2.0));

        const double worldX = player_.position_.getX() + distance * intersection.getDx();
        const double worldY = player_.position_.getY() + distance * intersection.getDy();

        return getPixelFromTexture(texture, toTexture(worldX), toTexture(worldY));
}

const Pixel FpvRenderer::getPixel(
        double y,
        double wallTop,
        double wallBottom,
        double lineHeight,
        Intersection &intersection
) {
	if (y < wallTop) {
		return getHorizontalPixel(y, intersection, "ceiling");
        } else if (y >= wallBottom) {
		return getHorizontalPixel(y, intersection, "floor");
        } else {
		return getWallPixel(y, lineHeight, wallTop, intersection);
        }
}

void FpvRenderer::drawVerticalLine(
	double x,
	Intersection &intersection
) {
	const double lineHeight = k_ / intersection.getDistance();
	
	const double wallTop = floor((height_ - lineHeight) / 2);
	const double wallBottom = floor((height_ + lineHeight) / 2);
	
        for (int y = 0; y < height_; y++) {
		const Pixel pixel = getPixel(y, wallTop, wallBottom, lineHeight, intersection);
		setPixel(x, y, pixel);
	}	
}

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



