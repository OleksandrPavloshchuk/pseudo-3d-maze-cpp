/**
 * loadTextures.hpp
 */
 
#pragma once

#include "constants.hpp"
#include "loadMaze.hpp"
#include "render/PixelBuffer.hpp"

bool loadTextures();
Pixel getPixelFromTexture(const char *name, int x, int y);


