#include "MasterRenderer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

MasterRenderer::MasterRenderer()
{
	glfwSetCursorPosCallback(_engineInstance->getWindow()->getHandle(), processMouseMovement);
}

void MasterRenderer::update()
{
	//Calculate delta time
	double currentTime = glfwGetTime();
	double deltaTime = _lastTime - currentTime;
	_lastTime = currentTime;

	if (_engineInstance->getCamera() != NULL)
	{
		checkCameraKeyEvent();
		_engineInstance->getCamera()->update();
	}

	for (auto& renderer : _renderers)
	{
		renderer->update(deltaTime);
	}
}

void MasterRenderer::draw()
{
	//std::cout << "View: " << glm::to_string(*_engineInstance->getCamera()->getViewMatrix()) << std::endl;

	for (auto& renderer : _renderers)
	{
		renderer->draw(&_projectionMatrix);
	}
}

void MasterRenderer::updateProjectionMatrix()
{
	CWINDOW* window = _engineInstance->getWindow();
	float aspectRatio = *(window->getWindowWidth()) / *(window->getWindowHeight());
	_projectionMatrix = glm::perspective(glm::radians(70.0f), aspectRatio, 0.1f, 100.0f);
}

void MasterRenderer::addRenderer(RendererBase* renderer)
{
	_renderers.push_back(renderer);
}

void MasterRenderer::checkCameraKeyEvent()
{
	Camera* camera = _engineInstance->getCamera();
	GLFWwindow* window = _engineInstance->getWindow()->getHandle();

	float cameraSpeed = 0.05f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->move(Camera::FORWARDS, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->move(Camera::BACKWARDS, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->move(Camera::LEFT, cameraSpeed);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->move(Camera::RIGHT, cameraSpeed);
}

void MasterRenderer::processMouseMovement(GLFWwindow* window, double xPos, double yPos)
{
	Engine::EngineInstance* engineInstance = Engine::EngineInstance::getInstance();
	engineInstance->getCamera()->updateTargetDirection(xPos, yPos);
}