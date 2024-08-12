#include "user/mesh.h"
#include "user/model_loader.h"
#include "user/node3d.h"
#include "user/physics_node3d.h"
#include "user/point_light.h"
#include "user/skybox.h"
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;
// define faces path array
unsigned int loadCubemap(vector<string> faces);
btDiscreteDynamicsWorld *init_physics();
GLFWwindow *init_renderer(int width, int height, const char *title);
unsigned int init_ubo_camera_matrices();
unsigned int init_ubo_point_lights();
void update_ubo_camera_matrices(unsigned int uboCameraMatrices, Camera &camera);
void update_ubo_point_lights(unsigned int uboPointLights, PointLight *lights, int lightCount);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera* main_camera;

int main()
{
	btDiscreteDynamicsWorld *dynamicsWorld = init_physics();

	GLFWwindow *window = init_renderer(width, height, "Bullet Physics");

	vector<std::string> faces{
		"../res/textures/skybox/right.jpg",
		"../res/textures/skybox/left.jpg",
		"../res/textures/skybox/top.jpg",
		"../res/textures/skybox/bottom.jpg",
		"../res/textures/skybox/front.jpg",
		"../res/textures/skybox/back.jpg"};

	Skybox skybox = Skybox(faces);
	cout << "Skybox created" << endl;
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

	PhysicsNode3D guitar = PhysicsNode3D(glm::vec3(-3.0f, 100.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.005f, 0.005f, 0.005f), guitarShader, "../res/models/lightball.dae", 15.0f);
	PhysicsNode3D level = PhysicsNode3D(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f), levelShader, "../res/models/castle.obj", 0.0f);
	dynamicsWorld->addRigidBody(level.rigidBody);
	dynamicsWorld->addRigidBody(guitar.rigidBody);

	PointLight pointLight = PointLight(glm::vec3(0.0f, -7.0f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.2f, 0.5f, 1.0f, 1.0f), .01, 0.0001f, 0.00001f, "../res/models/lightball.dae");

	cout << "objects created" << endl;
	int lightCount = 1;
	PointLight lights[1] = {pointLight};

	unsigned int uboCameraMatrices = init_ubo_camera_matrices();
	unsigned int uboPointLights = init_ubo_point_lights();

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	main_camera = &camera;
	cout << "camera created" << endl;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		double crntTime = glfwGetTime();
		// if (crntTime - prevTime >= 1 / 60)
		//{
		//	rotation += 0.5f;
		//	guitar.set_rotation(glm::vec3(0.0f, rotation, 0.0f));
		//	prevTime = crntTime;
		// }

		dynamicsWorld->stepSimulation(1 / 60.0f, 10, 1 / 60.0f);

		guitar.update();
		level.update();

		camera.Inputs(window);
		camera.updateMatrix(70.0f, 0.1f, 100.0f);

		update_ubo_camera_matrices(uboCameraMatrices, camera);
		update_ubo_point_lights(uboPointLights, lights, lightCount);

		guitar.draw();
		level.draw();
		pointLight.draw();

		skybox.draw(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	main_camera->width = width;
	main_camera->height = height;
	main_camera->updateMatrix(70.0f, 0.1f, 100.0f);
    glViewport(0, 0, width, height);
}  

void update_ubo_camera_matrices(unsigned int uboCameraMatrices, Camera &camera)
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera.cameraMatrix));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(camera.Position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void update_ubo_point_lights(unsigned int uboPointLights, PointLight *lights, int lightCount)
{
	for (int i = 0; i < lightCount; i++)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, uboPointLights);
		glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)), sizeof(glm::vec3), glm::value_ptr(lights[i].position));
		glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3), sizeof(glm::vec4), glm::value_ptr(lights[i].lightColor));
		glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3) + sizeof(glm::vec4), sizeof(float), &lights[i].linear);
		glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(float), sizeof(float), &lights[i].quadratic);
		glBufferSubData(GL_UNIFORM_BUFFER, i * (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) + sizeof(glm::vec3) + sizeof(glm::vec4) + 2 * sizeof(float), sizeof(float), &lights[i].constant);

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

unsigned int init_ubo_camera_matrices()
{
	unsigned int uboCameraMatrices;
	glGenBuffers(1, &uboCameraMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) + sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboCameraMatrices, 0, sizeof(glm::mat4) + sizeof(glm::vec3));
	return uboCameraMatrices;
}

unsigned int init_ubo_point_lights()
{
	unsigned int pointLights;
	glGenBuffers(1, &pointLights);

	glBindBuffer(GL_UNIFORM_BUFFER, pointLights);
	glBufferData(GL_UNIFORM_BUFFER, (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) * 1, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, pointLights, 0, (sizeof(glm::vec3) + sizeof(glm::vec4) + 3 * sizeof(float)) * 1);
	return pointLights;
}

btDiscreteDynamicsWorld *init_physics()
{
	btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btBroadphaseInterface *overlappingPairCache = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver();
	btDiscreteDynamicsWorld *dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -5.0, 0)); // Set gravity
	return dynamicsWorld;
}

unsigned int loadCubemap(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

GLFWwindow *init_renderer(int width, int height, const char *title)
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//// Create a window
	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Can't create glfw window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	gladLoadGL();

	// Set the viewport, and a bg color -> then swap the buffers
	glViewport(0, 0, width, height);

	return window;
}