set(PROJECT_NAME "pseudo-3d-maze")

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release")

set(SRC_MAIN "src")

project(${PROJECT_NAME}
	VERSION 1.0
    	LANGUAGES CXX
)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
	${SRC_MAIN}/main.cpp
	${SRC_MAIN}/loadMaze.cpp
	${SRC_MAIN}/loadTextures.cpp
	${SRC_MAIN}/TrigonometryCache.cpp
	${SRC_MAIN}/PerformanceMeter.cpp
	${SRC_MAIN}/model/Point.cpp
	${SRC_MAIN}/model/MazeCell.cpp
	${SRC_MAIN}/model/Maze.cpp
	${SRC_MAIN}/model/Intersection.cpp
	${SRC_MAIN}/model/IntersectionsDetector.cpp	
	${SRC_MAIN}/model/Player.cpp
	${SRC_MAIN}/render/PixelBuffer.cpp
	${SRC_MAIN}/render/Renderer.cpp
	${SRC_MAIN}/render/FpvRenderer.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Wshadow
)

find_package(SDL3 REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

find_package(SDL3_image REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/textures"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/textures"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/mazes"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/mazes"
)

#file(COPY textures DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY mazes DESTINATION ${CMAKE_BINARY_DIR})


