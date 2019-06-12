#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <iostream>

#include "Camera.h"

extern GLFWwindow* windowHandle;

#define SENSITIVITY 0.25f;

Camera::Camera(glm::vec3 position, float fieldOfView)
{
	_position = position;
	_fov = fieldOfView;

	createViewMatrix();

	std::cout << "Created camera." << std::endl;
}

void Camera::updateVectors()
{
	//Re-calcualte front vector
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	newFront.y = sin(glm::radians(_pitch));
	newFront.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_cameraFront = glm::normalize(newFront);

	//Re-calculate right vector
	_cameraRight = glm::normalize(glm::cross(_cameraFront, _worldUp));

	//Re-calculate up vector
	_cameraUp	= glm::normalize(glm::cross(_cameraRight, _cameraFront));
}

void Camera::updateTargetDirection(double& mouseX, double& mouseY)
{
	float xOffset = mouseX - _lastX;
	float yOffset = _lastY - mouseY; //reversed because y range from bottom to top
	_lastX = mouseX;
	_lastY = mouseY;

	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	_yaw += xOffset;
	_pitch += yOffset;

	//Camera constraints
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	updateVectors();
}

void Camera::move(Camera::MoveDirection direction, float speed)
{

	if		(direction == FORWARDS)		_position += speed * _cameraFront;
	else if (direction == BACKWARDS)	_position -= speed * _cameraFront;
	else if (direction == LEFT)			_position -= _cameraRight * speed;
	else if (direction == RIGHT)		_position += _cameraRight * speed;
}

void Camera::update()
{
	updateVectors();
	createViewMatrix();
}

void Camera::createViewMatrix()
{
	_viewMatrix = glm::lookAt(_position, _position + _cameraFront, _cameraUp);
}

glm::vec3* Camera::getPosition()
{
	return &_position;
}

void Camera::setPosition(glm::vec3* position)
{
	_position = *position;
}

void Camera::translate(glm::vec3 translation)
{
	_position.x += translation.x;
	_position.y += translation.y;
	_position.z += translation.z;
	update();
}

glm::mat4* Camera::getViewMatrix()
{
	return &_viewMatrix;
}

