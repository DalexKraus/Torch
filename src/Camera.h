#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	private:
		float _fov		= 70.0f;
		float _yaw		= -90.0f;
		float _pitch	= 0.0f;
		float _lastX;
		float _lastY;

		glm::vec3 _position;
		glm::vec3 _cameraTarget;
		glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 _cameraUp;
		glm::vec3 _cameraRight;

		glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 _viewMatrix;
		void createViewMatrix();
		void updateVectors();

	public:
		enum MoveDirection
		{
			FORWARDS,
			BACKWARDS,
			LEFT,
			RIGHT
		};

		Camera(glm::vec3 position, float fieldOfView);
		glm::vec3* getPosition();
		glm::mat4* getViewMatrix();
		void update();
		void setPosition(glm::vec3* position);
		void translate(glm::vec3 translation);
		void updateTargetDirection(double& xPos, double& yPos);
		void move(MoveDirection direction, float speed);

};

#endif