/**
 * PixelBuffer.hpp
 */
 
#pragma once
 
#include <cstdint>
#include <vector>

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

class PixelBuffer {
public:
    PixelBuffer(
    	int width, 
    	int height
    ):
    	width_(width),
    	height_(height),
    	pixels_(width * height, Pixel{})
    {
    }
    
    double getHeight() const { return height_; }

    void clear();
    void setPixel(int x, int y, Pixel pixel);
    
    const std::vector<Pixel>& getPixels() const { return pixels_; }
    int getWidth() const { return width_; } 

private:

    int width_;
    int height_;
    std::vector<Pixel> pixels_;
};
