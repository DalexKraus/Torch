#ifndef ENGINE_H
#define ENGINE_H

#include "CWindow.h"
#include "Camera.h"

namespace Engine
{

	//Singleton concept
	//
	class EngineInstance
	{
		private:
			static EngineInstance*	_engineInstance;
			CWINDOW*				_window;
			Camera*					_camera;

			/* Private constructor to prevent instancing */
			EngineInstance();

		public:
			void			initialize(int windowWidth, int windowHeight, std::string windowTitle, bool isResizeable);
			CWINDOW*		getWindow();
			Camera*			getCamera();
			static EngineInstance* getInstance();
	};
}

#endif