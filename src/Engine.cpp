#include "Engine.h"

namespace Engine
{
	EngineInstance* EngineInstance::_engineInstance = NULL;
	
	EngineInstance* EngineInstance::getInstance()
	{
		if (_engineInstance == NULL)
		{
			_engineInstance = new EngineInstance();
		}
		return _engineInstance;
	}

	EngineInstance::EngineInstance() {};

	void EngineInstance::initialize(int windowWidth, int windowHeight, std::string windowTitle, bool isResizeable)
	{
		_engineInstance->_window = new CWINDOW(windowWidth, windowHeight, windowTitle, isResizeable);
		_engineInstance->_camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), 70);
	}

	CWINDOW* EngineInstance::getWindow()
	{
		return _engineInstance->_window;
	}

	Camera* EngineInstance::getCamera()
	{
		return _engineInstance->_camera;
	}
}