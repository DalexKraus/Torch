#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Texture.h"
#include "FileUtil.h"
#include "MasterRenderer.h"
#include "EntityRenderer.h"
#include "Entity.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

	//Texture* tex = Texture::readTextureFromFile("container.jpg");
	masterRenderer = new MasterRenderer();
	EntityRenderer* entityRenderer = new EntityRenderer();
	VertexArrayObject vao = VertexArrayObject();
	
	float vertices[] = {
		-0.5f, 0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		0.5f, 0.5f, -1.0f
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

	//ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(engine->getWindow()->getHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 150");
	ImGui::StyleColorsDark();

	bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	double time;

	glClearColor(0.5f, 0.0f, 0.25f, 1.0f);
	while (!glfwWindowShouldClose(engine->getWindow()->getHandle()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

		masterRenderer->update();
		masterRenderer->draw();

		//My Gui
		{
			ImGui::Begin("Profiling");

			double deltaTime = glfwGetTime() - time;
			time = glfwGetTime();

			ImGui::Text("Time Usage:");
			ImGui::Text("Delta Time: %.3f s/frame", deltaTime);
			ImGui::Text("Camera:");
			Camera* camera = engine->getCamera();
			ImGui::Text("X: %.3f Y: %.3f Z: %.3f", 0.0f, 0.0f, 0.0f);

			ImGui::End();
		}

		 // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

		// 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(engine->getWindow()->getHandle());
		glfwPollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}
