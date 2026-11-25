/**
 * main.cpp
 */
 
#include <SDL3/SDL.h>

#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <array>
#include <string>

#include "constants.hpp"
#include "loadMaze.hpp"
#include "loadTextures.hpp"
#include "model/Player.hpp"
#include "model/Maze.hpp"
#include "render/FpvRenderer.hpp"

// Global variables
const int playerWallGap = 6;

const int fpvWidth = 800;
const int fpvHeight = 600;

std::filesystem::path getExecutableDir() {
    std::array<char, 4096> buffer{};

    const auto size = readlink(
        "/proc/self/exe",
        buffer.data(),
        buffer.size() - 1
    );

    if (size == -1) {
        throw std::runtime_error("Cannot determine executable path");
    }

    return std::filesystem::path(
        std::string(buffer.data(), size)
    ).parent_path();
}


// Entry point
int main() {

	auto executableDir = getExecutableDir();
	
	if (!loadTextures(executableDir)) {
		return 1;
	}
	
	const std::filesystem::path filePath = executableDir / "mazes/3.txt";	

    	const Maze maze = loadMaze( filePath, playerWallGap);

    	const DoublePoint startPos(
        	TEXTURE_SIZE * 1.5,
        	TEXTURE_SIZE * 1.5
    	);

    	Player player(startPos, fpvWidth);
    	
    	FpvRenderer renderer(fpvWidth, fpvHeight, maze, player);
    	if (!renderer.initialize()) {
    		return 1;
    	}    	
    	renderer.mainLoop();
    	
    	return 0;
    		
}
