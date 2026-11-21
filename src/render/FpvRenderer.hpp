/**
 * FpvRenderer.hpp
 */
 
#pragma once

#include "Renderer.hpp"

class FpvRenderer : public Renderer {
public:
	FpvRenderer(int width, int height):
		Renderer("Pseudo 3D Maze (2)", width, height)
	{
	}
protected:
	void updateFrameBuffer();
};
