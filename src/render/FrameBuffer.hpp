/**
 * FrameBuffer.hpp
 */
 
#pragma once
 
#include <cstdint>
#include <vector>
 
class FrameBuffer {
public:
    FrameBuffer(
    	int width, 
    	int height
    ):
    	width_(width),
    	height_(height),
    	pixels_(width * height, 0)
    {
    }

    void clear();
    void setPixel(int x, int y, uint32_t color);
    
    const std::vector<uint32_t>& getPixels() const { return pixels_; }
    int getWidth() const { return width_; } 

private:
    int width_;
    int height_;
    std::vector<uint32_t> pixels_;
};
