/**
 * main.cpp
 */
 
#include <SDL3/SDL.h>

#include "constants.hpp"
#include "loadMaze.hpp"
#include "model/Point.hpp"
#include "model/MazeCell.hpp"
#include "model/Intersection.hpp"
#include "model/IntersectionsDetector.hpp"
#include "model/Maze.hpp"
#include "render/FpvRenderer.hpp"

// Global variables
const int playerWallGap = 6;

const int fpvWidth = 800;
const int fpvHeight = 640;

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

    	const Player player(startPos, fpvWidth);
    	
    	FpvRenderer renderer(fpvWidth, fpvHeight);
    	if (!renderer.initialize()) {
    		return 1;
    	}
    	renderer.mainLoop();
    		
}
