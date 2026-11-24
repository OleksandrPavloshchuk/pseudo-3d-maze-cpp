/**
 * loadTextures.hpp
 */
 
#pragma once

#include <filesystem>

#include "constants.hpp"
#include "loadMaze.hpp"
#include "render/PixelBuffer.hpp"

bool loadTextures(std::filesystem::path &executableDir);
Pixel getPixelFromTexture(const char *name, int x, int y);


