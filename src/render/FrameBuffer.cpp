/**
 * FrameBuffer.cpp
 */
 
#include "FrameBuffer.hpp"

void FrameBuffer::clear() {
	std::fill(pixels_.begin(), pixels_.end(), Pixel{});
}

void FrameBuffer::setPixel(int x, int y, Pixel pixel) {
	pixels_[x + y * width_] = pixel;
}
