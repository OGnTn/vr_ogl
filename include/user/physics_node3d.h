#ifndef PHYSICS_NODE3D_H
#define PHYSICS_NODE3D_H

#include "user/node3d.h"
#include "user/shape_factory.h"
#include <btBulletDynamicsCommon.h>

class PhysicsNode3D : public Node3D
{
public:
    PhysicsNode3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader &shader, std::string model_file_path, float mass);
    PhysicsNode3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader &shader, std::string model_file_path, float mass, btCollisionShape *collisionShape);
    void update(float deltaTime);
    btRigidBody *rigidBody;
    void update();

private:
    float mass;
    btRigidBody *create_rigid_body(btCollisionShape *collisionShape);
    void update_scale();
};

#endif