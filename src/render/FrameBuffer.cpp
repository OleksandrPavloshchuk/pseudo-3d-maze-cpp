/**
 * FrameBuffer.cpp
 */
 
#include "FrameBuffer.hpp"

void FrameBuffer::clear() {
/*
	for (int i=0; i<width_*height_; i++) {
		pixels_[i] = 0;
	}
*/
	std::fill(pixels_.begin(), pixels_.end(), 0);
}

void FrameBuffer::setPixel(int x, int y, uint32_t color) {
	pixels_[x + y * width_] = color;
}
