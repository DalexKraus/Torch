#include "CWindow.h"

CWINDOW::CWINDOW(int width, int height, std::string title, bool resizeable)
{
	_width = width;
	_height = height;
	_windowTitle = title;
	_isResizeable = resizeable;

	createWindow();
}

void CWINDOW::createWindow()
{
	glfwInit();
	
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	glfwWindowHint(GLFW_RESIZABLE, _isResizeable);

	_windowHandle = glfwCreateWindow(_width, _height, _windowTitle.c_str(), NULL, NULL);
	if (_windowHandle == NULL)
	{
		std::cout << "Unable to create GLFW Window!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(_windowHandle);
	glfwSetInputMode(_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return;
	}

	glViewport(0, 0, _width, _height);
	glfwSwapInterval(1);
}

int* CWINDOW::getWindowWidth()
{
	return &_width;
}

int* CWINDOW::getWindowHeight()
{
	return &_height;
}

std::string* CWINDOW::getWindowTitle()
{
	return &_windowTitle;
}

GLFWwindow* CWINDOW::getHandle()
{
	return _windowHandle;
}

void CWINDOW::setTitle(std::string title)
{
	_windowTitle = title;
	glfwSetWindowTitle(_windowHandle, title.c_str());
}