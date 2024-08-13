#include "user/node3d.h"

Node3D::Node3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader &shader, std::string model_file_path) : shader(shader)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->shader = shader;
    ModelLoader::load_model(model_file_path, this->meshes);
    update_model();
}

void Node3D::assign_meshes(std::vector<Mesh> meshes)
{
    this->meshes = meshes;
}

void Node3D::set_position(glm::vec3 position)
{
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
    // std::cout << "Position: " << this->position.x << ", " << this->position.y << ", " << this->position.z << std::endl;
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

void Node3D::draw()
{
    this->shader.Activate();
    GLuint modelLoc = glGetUniformLocation(this->shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->model));

    for (Mesh mesh : this->meshes)
    {
        // mesh.shader.Activate();
        // GLuint modelLoc = glGetUniformLocation(mesh.shader.ID, "model");
        if (modelLoc == GL_INVALID_VALUE)
        {
            std::cout << "Invalid model location" << std::endl;
        }
        else if (modelLoc == GL_INVALID_OPERATION)
        {
            std::cout << "Invalid operation" << std::endl;
        }
        else
        {
            // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->model));
            mesh.Draw();
        }
    }
}