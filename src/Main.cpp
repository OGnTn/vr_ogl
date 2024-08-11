#include "user/mesh.h"
#include "user/model_loader.h"
#include "user/node3d.h"
#include "user/point_light.h"
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;
unsigned int loadCubemap(vector<string> faces);

int main()
{
	// Bullet Physics initialization
	btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btBroadphaseInterface *overlappingPairCache = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver();
	btDiscreteDynamicsWorld *dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -1.0, 0)); // Set gravity

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

	Shader skyboxShader("../res/shaders/skybox.vert", "../res/shaders/skybox.frag");

	float skyboxVertices[] = {
		// positions
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f};

	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	// load textures
	// -------------
	// unsigned int cubeTexture = loadTexture(FileSystem::getPath("resources/textures/container.jpg").c_str());

	vector<std::string> faces{
		"../res/textures/skybox/right.jpg",
		"../res/textures/skybox/left.jpg",
		"../res/textures/skybox/top.jpg",
		"../res/textures/skybox/bottom.jpg",
		"../res/textures/skybox/front.jpg",
		"../res/textures/skybox/back.jpg"};
	unsigned int cubemapTexture = loadCubemap(faces);

	// shader configuration
	// --------------------

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

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
	Node3D guitar = Node3D(glm::vec3(0.0f, 100.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), guitarShader);
	guitar.assign_meshes(model_meshes);

	std::vector<Mesh> model_meshes2 = std::vector<Mesh>();
	modelLoader.load_model("../res/models/castle.obj", model_meshes2);
	Node3D level = Node3D(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f), levelShader);
	level.assign_meshes(model_meshes2);

	// Create the level's collision shape (BvhTriangleMeshShape)
	btTriangleMesh *levelMesh = new btTriangleMesh();
	for (const auto &mesh : model_meshes2)
	{
		for (size_t i = 0; i < mesh.indices.size(); i += 3)
		{
			btVector3 v0(mesh.vertices[mesh.indices[i]].Position.x, mesh.vertices[mesh.indices[i]].Position.y, mesh.vertices[mesh.indices[i]].Position.z);
			btVector3 v1(mesh.vertices[mesh.indices[i + 1]].Position.x, mesh.vertices[mesh.indices[i + 1]].Position.y, mesh.vertices[mesh.indices[i + 1]].Position.z);
			btVector3 v2(mesh.vertices[mesh.indices[i + 2]].Position.x, mesh.vertices[mesh.indices[i + 2]].Position.y, mesh.vertices[mesh.indices[i + 2]].Position.z);
			levelMesh->addTriangle(v0, v1, v2);
		}
	}

	btBvhTriangleMeshShape *convexHullShape = new btBvhTriangleMeshShape(levelMesh, true);
	convexHullShape->recalcLocalAabb(); // Recalculate the AABB after adding points
	convexHullShape->setLocalScaling(btVector3(level.scale.x, level.scale.y, level.scale.z));

	// Create the static body
	btScalar mass = 0.0f;			 // Static body has zero mass
	btVector3 localInertia(0, 0, 0); // No inertia for static body
	convexHullShape->calculateLocalInertia(mass, localInertia);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(level.position.x, level.position.y, level.position.z)); // Set the desired position

	btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, convexHullShape, localInertia);
	btRigidBody *staticBody = new btRigidBody(rbInfo);

	// Add the static body to the dynamics world
	dynamicsWorld->addRigidBody(staticBody);

	// dynamicsWorld->addRigidBody(levelBody);

	// Extract vertices from the guitar mesh to create a collision shape
	btConvexHullShape *guitarShape = new btConvexHullShape();
	for (const auto &mesh : guitar.meshes)
	{
		for (const auto &vertex : mesh.vertices)
		{
			guitarShape->addPoint(btVector3(vertex.Position.x, vertex.Position.y, vertex.Position.z));
		}
	}
	guitarShape->setLocalScaling(btVector3(guitar.scale.x, guitar.scale.y, guitar.scale.z));
	guitarShape->recalcLocalAabb();

	// Create a rigid body for the guitar
	btScalar guitarMass = 1.0f;
	btVector3 guitarInertia(0, 0, 0);
	guitarShape->calculateLocalInertia(guitarMass, guitarInertia);

	btTransform guitarTransform;
	guitarTransform.setIdentity();
	guitarTransform.setOrigin(btVector3(guitar.position.x, guitar.position.y, guitar.position.z));

	btDefaultMotionState *guitarMotionState = new btDefaultMotionState(guitarTransform);
	btRigidBody::btRigidBodyConstructionInfo guitarRbInfo(guitarMass, guitarMotionState, guitarShape, guitarInertia);
	btRigidBody *guitarBody = new btRigidBody(guitarRbInfo);

	dynamicsWorld->addRigidBody(guitarBody);

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
		// if (crntTime - prevTime >= 1 / 60)
		//{
		//	rotation += 0.5f;
		//	guitar.set_rotation(glm::vec3(0.0f, rotation, 0.0f));
		//	prevTime = crntTime;
		// }

		dynamicsWorld->stepSimulation(1 / 60.0f, 10, 1 / 60.0f);

		// Update guitar position and rotation from Bullet
		btTransform trans;
		guitarBody->getMotionState()->getWorldTransform(trans);

		btVector3 btPosition = trans.getOrigin();
		btQuaternion btRotation = trans.getRotation();

		guitar.set_position(glm::vec3(btPosition.getX(), btPosition.getY(), btPosition.getZ()));
		guitar.set_rotation(glm::vec3(btRotation.getX(), btRotation.getY(), btRotation.getZ()));
		cout << "Position: " << glm::to_string(guitar.position) << endl;

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

		glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.Activate();
		glm::mat4 m_view = glm::mat4(glm::mat3(camera.view)); // remove translation from the view matrix
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
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
