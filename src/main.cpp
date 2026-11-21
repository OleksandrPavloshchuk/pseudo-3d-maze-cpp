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

// Global variables
const int playerWallGap = 6;

const int fpvWidth = 800;
const int fpvHeight = 640;

void initialize(const Maze &maze, const Player &player) {
	// TODO
}

bool initialize(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(
        "Pseudo 3D Maze",
        fpvWidth,
        fpvHeight,
        0,
        &window,
        &renderer
    )) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

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

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initialize(window, renderer)) {
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
