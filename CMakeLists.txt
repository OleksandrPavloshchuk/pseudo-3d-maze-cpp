set(PROJECT_NAME "pseudo-3d-maze")

cmake_minimum_required(VERSION 4.00)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

set(SRC_MAIN "src")

project(${PROJECT_NAME}
	VERSION 1.0
    	LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
	${SRC_MAIN}/main.cpp
)


# find_package(Drogon REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Wshadow
)
