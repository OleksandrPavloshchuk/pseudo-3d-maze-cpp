set(PROJECT_NAME "pseudo-3d-maze")

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SRC_MAIN "src")

project(${PROJECT_NAME}
	VERSION 1.0
    	LANGUAGES CXX
)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
	${SRC_MAIN}/main.cpp
	${SRC_MAIN}/loadMaze.cpp
	${SRC_MAIN}/model/Point.cpp
	${SRC_MAIN}/model/MazeCell.cpp
	${SRC_MAIN}/model/Maze.cpp
	${SRC_MAIN}/model/Intersection.cpp
	${SRC_MAIN}/model/IntersectionsDetector.cpp	
	${SRC_MAIN}/model/Player.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Wshadow
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
