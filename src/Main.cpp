#include "user/mesh.h"
#include "user/model_loader.h"
#include "user/node3d.h"
#include "user/point_light.h"
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//// Create a window
	GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Can't create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	gladLoadGL();

	// Set the viewport, and a bg color -> then swap the buffers
	glViewport(0, 0, width, height);

	// Texture textures[]{
	//	Texture("../res/textures/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	Texture("../res/textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE);
	//};

	// Compile and link the vertex and frag shaders into shaderprogram
	Shader guitarShader("../res/shaders/def.vert", "../res/shaders/def.frag");
	Shader levelShader("../res/shaders/def.vert", "../res/shaders/def.frag");

	ModelLoader modelLoader;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	std::vector<Mesh> model_meshes = std::vector<Mesh>();
	modelLoader.load_model("../res/models/guitar.glb", model_meshes);
	Node3D guitar = Node3D(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.001f, 0.001f, 0.001f), guitarShader);
	guitar.assign_meshes(model_meshes);

	std::vector<Mesh> model_meshes2 = std::vector<Mesh>();
	modelLoader.load_model("../res/models/scene.gltf", model_meshes2);
	Node3D level = Node3D(glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), levelShader);
	level.assign_meshes(model_meshes2);

	PointLight pointLight = PointLight(glm::vec3(0.0f, 1.0f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.3f, 0.1f);

	int lightCount = 1;
	PointLight lights[1] = {pointLight};

	unsigned int pointLights;
	glGenBuffers(1, &pointLights);

	glBindBuffer(GL_UNIFORM_BUFFER, pointLights);
	glBufferData(GL_UNIFORM_BUFFER, (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) * lightCount, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, pointLights, 0, (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) * lightCount);

	unsigned int uboCameraMatrices;
	glGenBuffers(1, &uboCameraMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) + sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboCameraMatrices, 0, sizeof(glm::mat4) + sizeof(glm::vec3));

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			guitar.set_rotation(glm::vec3(0.0f, rotation, 0.0f));
			prevTime = crntTime;
		}

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera.cameraMatrix));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(camera.Position));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		for (int i = 0; i < 1; i++)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, pointLights);
			glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)), sizeof(glm::vec3), glm::value_ptr(lights[i].position));
			glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3), sizeof(glm::vec4), glm::value_ptr(lights[i].lightColor));
			glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3) + sizeof(glm::vec4), sizeof(float), &lights[i].linear);
			glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(float), sizeof(float), &lights[i].quadratic);
			glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3) + sizeof(glm::vec4) + 2 * sizeof(float), sizeof(float), &lights[i].constant);

			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		guitar.draw();
		level.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
