#ifndef CWINDOW_H
#define CWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class CWINDOW
{
public:
	int*			getWindowWidth();
	int*			getWindowHeight();
	bool*			isResizeable();
	std::string*	getWindowTitle();
	GLFWwindow*		getHandle();

	void			setTitle(std::string title);

	CWINDOW(int width, int height, std::string title, bool resizeable);

private:
	int				_width, _height;
	bool			_isResizeable;
	std::string		_windowTitle;
	GLFWwindow*		_windowHandle;

	void			createWindow();
};

#endif