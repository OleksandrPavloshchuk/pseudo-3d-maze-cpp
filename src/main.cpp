/**
 * main.cpp
 */
 
#include <SDL3/SDL.h>

#include "constants.hpp"
#include "loadMaze.hpp"
#include "model/Player.hpp"
#include "model/Maze.hpp"
#include "render/FpvRenderer.hpp"

// Global variables
const int playerWallGap = 6;

const int fpvWidth = 640;
const int fpvHeight = 480;

// Entry point
int main() {
    	const Maze maze = loadMaze(
        	"/home/oleksandr/personal/c++/pseudo-3d-maze-cpp/mazes/3.txt",
        	playerWallGap
    	);

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
