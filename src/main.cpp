#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Texture.h"
#include "FileUtil.h"
#include "MasterRenderer.h"
#include "EntityRenderer.h"
#include "Entity.h"

#define WIDTH 720
#define HEIGHT 720

Engine::EngineInstance* engine;
MasterRenderer* masterRenderer;

void mouse(GLFWwindow* window, double x, double y)
{
	double xPos = x / 5.0f;
	double yPos = y / 5.0f;
	engine->getCamera()->updateTargetDirection(xPos, yPos);
}

int main()
{
	engine = Engine::EngineInstance::getInstance();
	engine->initialize(1920, 1080, "OpenGL | GLFW", true);

	glfwSetCursorPosCallback(engine->getWindow()->getHandle(), mouse);

	Texture* tex = Texture::readTextureFromFile("textures/container.jpg");
	masterRenderer = new MasterRenderer();
	EntityRenderer* entityRenderer = new EntityRenderer();
	VertexArrayObject vao = VertexArrayObject();
	
	float vertices[] = {
		-0.5f, 0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		0.5f, 0.5f, -1.0f,
	};

	unsigned int indices[] = {
		0, 1, 3, 3, 1, 2
	};

	size_t verticesSize = sizeof(vertices);
	size_t indicesSize = sizeof(indices);

	vao.storeIndicesList(indices, indicesSize, 6);
	vao.storeDataInAttributeList(0, vertices, verticesSize, 3);

	int indexCount = 6;
	Entity* entity = new Entity(vao, indexCount);
	entityRenderer->addEntity(entity);
	masterRenderer->addRenderer(entityRenderer);
	Camera* camera = engine->getCamera();
	masterRenderer->updateProjectionMatrix();

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
	camera->setPosition(&pos);

	glClearColor(0.5f, 0.0f, 0.25f, 1.0f);
	while (!glfwWindowShouldClose(engine->getWindow()->getHandle()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		masterRenderer->update();
		masterRenderer->draw();

		glfwSwapBuffers(engine->getWindow()->getHandle());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
