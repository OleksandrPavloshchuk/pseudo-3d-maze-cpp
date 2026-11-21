/**
 * FpvRenderer.cpp
 */
 
#include "FpvRenderer.hpp"

void FpvRenderer::updateFrameBuffer() {
	// TODO temporary test
	for (int x=0; x<width_; x++) {
		for (int y=0; y<height_; y++) {
			Pixel pixel{
				(uint8_t) ((x) % 256),
				(uint8_t) ((x + y) % 256),
				(uint8_t) ((y) % 256),
				(uint8_t) 255
			};
			
			setPixel(x, y, pixel);
		}	
	}
}

