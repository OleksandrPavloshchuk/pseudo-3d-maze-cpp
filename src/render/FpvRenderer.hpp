/**
 * FpvRenderer.hpp
 */
 
#pragma once

#include "Renderer.hpp"

class FpvRenderer : public Renderer {
public:
	FpvRenderer(int width, int height):
		Renderer(width, height)
	{
	}
protected:
	void updateFrameBuffer();
};
