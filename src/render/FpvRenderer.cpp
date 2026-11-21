/**
 * FpvRenderer.cpp
 */
 
#include <cmath>
 
#include "FpvRenderer.hpp"
#include "../model/MazeCell.hpp"


// TODO temporary until real textures rendering

const Pixel PIXEL_CEILING{204, 204, 255, 255};
const Pixel PIXEL_FLOOR{153, 153, 153, 255};
const Pixel PIXEL_WALL{153, 204, 153, 255};
const Pixel PIXEL_PICTURE{204, 102, 153, 255};
const Pixel PIXEL_WINDOW{204, 204, 255, 255};
const Pixel PIXEL_EXIT_DOOR{255, 255, 204, 255};

const Pixel getWallPixel(MazeCellType type) {
	switch(type) {
	case MazeCellType::WALL:
		return PIXEL_WALL;
	case MazeCellType::WINDOW:
		return PIXEL_WINDOW;	
	case MazeCellType::PICTURE:
		return PIXEL_PICTURE;	
	default:
		return PIXEL_EXIT_DOOR;	
	}
}

void FpvRenderer::updateFrameBuffer() {
	// TODO temporary test
	for (int x=0; x<width_; x++) {
		for (int y=0; y<height_; y++) {
			if (x % 64 > 4) {
				const int fx = (int) ((sqrt(x) * y + sqrt(y) * x) * 10 );
				const int fy = (int) (x * x + y * y + x + y) ;
				const int fz = (int) (sqrt(x + y) * x * y);
		
				Pixel pixel{
					(uint8_t) (fx % 256),
					(uint8_t) (fy % 256),
					(uint8_t) (fz % 256),
					(uint8_t) 255
				};
			
				setPixel(x, y, pixel);
			} else {
				setPixel(x, y, y % 64 > 6 ? PIXEL_EXIT_DOOR : PIXEL_WALL);
			}
		}	
	}
}

