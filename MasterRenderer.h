#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <vector>
#include "RendererBase.h"

class MasterRenderer
{
	private:
		Engine::EngineInstance*		_engineInstance;
		glm::mat4					_projectionMatrix;
		double						_lastTime = 0.0f;
		
		std::vector<RendererBase*>	_renderers;
		
		void checkCameraKeyEvent();
		static void processMouseMovement(GLFWwindow* window, double xPos, double yPos);

	public:
		MasterRenderer();

		void addRenderer(RendererBase* renderer);
		void updateProjectionMatrix();
		
		void update();
		void draw();
		
};

#endif