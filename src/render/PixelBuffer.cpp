/**
 * PixelBuffer.cpp
 */
 
#include "PixelBuffer.hpp"

void PixelBuffer::clear() {
	std::fill(pixels_.begin(), pixels_.end(), Pixel{});
}

void PixelBuffer::setPixel(int x, int y, Pixel pixel) {
	pixels_[x + y * width_] = pixel;
}
