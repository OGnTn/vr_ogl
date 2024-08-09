#include "user/node3d.h"

Node3D::Node3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader& shader): shader(shader)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->shader = shader;
    update_model();
}

void Node3D::assign_meshes(std::vector<Mesh> meshes)
{
    this->meshes = meshes;
}

void Node3D::set_position(glm::vec3 position)
{
    this->position = position;
    update_model();
    }

void Node3D::set_rotation(glm::vec3 rotation)
{
    this->rotation = rotation;
    update_model();
}

void Node3D::set_scale(glm::vec3 scale)
{
    this->scale = scale;
    update_model();
}

void Node3D::update_model()
{
    this->model = glm::mat4(1.0f);
    this->model = glm::translate(this->model, this->position);
    this->model = glm::rotate(this->model, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->model = glm::rotate(this->model, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->model = glm::rotate(this->model, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->model = glm::scale(this->model, this->scale);
}

void Node3D::draw(Camera& camera, glm::vec4 lightColor, glm::vec3 lightPos){
    shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(this->model));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    for (Mesh mesh : this->meshes){
        mesh.Draw(this->shader, camera);
    }
}