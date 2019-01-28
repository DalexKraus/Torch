#ifndef RENDERERBASE_H
#define RENDERERBASE_H

#include "Engine.h"
#include <iostream>

class RendererBase
{
	private:
					
	public:
		virtual void update(double& deltaTime) = 0;
		virtual void draw(glm::mat4* projectionMatrix) = 0;

};

#endif