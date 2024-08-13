#include "user/physics_node3d.h"

PhysicsNode3D::PhysicsNode3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader &shader, std::string model_file_path, float mass) : Node3D(position, rotation, scale, shader, model_file_path)
{
    this->mass = mass;
    if (this->mass != 0.0f)
    {
        btCollisionShape *collisionShape = ShapeFactory::createConvexHullShape(this->meshes);
        this->rigidBody = create_rigid_body(collisionShape);
    }
    else
    {
        btCollisionShape *collisionShape = ShapeFactory::createBvhTriangleMeshShape(this->meshes);
        this->rigidBody = create_rigid_body(collisionShape);
    }
    update_scale();
}

PhysicsNode3D::PhysicsNode3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader &shader, std::string model_file_path, float mass, btCollisionShape *collisionShape) : Node3D(position, rotation, scale, shader, model_file_path)
{
    this->mass = mass;
}

btRigidBody *PhysicsNode3D::create_rigid_body(btCollisionShape *collisionShape)
{
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(this->position.x, this->position.y, this->position.z));
    transform.setRotation(btQuaternion(this->rotation.x, this->rotation.y, this->rotation.z));

    btVector3 localInertia(0, 0, 0);
    if (this->mass != 0.0f)
    {
        btScalar _mass(this->mass);
        collisionShape->calculateLocalInertia(_mass, localInertia);
    }

    // localInertia /= 10.0f;
    std::cout << "Local inertia: " << localInertia.getX() << ", " << localInertia.getY() << ", " << localInertia.getZ() << std::endl;
    btDefaultMotionState *motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(this->mass, motionState, collisionShape, localInertia);
    btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);
    return rigidBody;
}

void PhysicsNode3D::update()
{
    btTransform transform;
    this->rigidBody->getMotionState()->getWorldTransform(transform);
    btVector3 origin = transform.getOrigin();
    // std::cout << "Position: " << origin.getX() << ", " << origin.getY() << ", " << origin.getZ() << std::endl;
    this->set_position(glm::vec3(origin.getX(), origin.getY(), origin.getZ()));
    btQuaternion rotation = transform.getRotation();
    float x, y, z;
    rotation.getEulerZYX(z, y, x);
    // this->set_rotation(glm::vec3(x, y, z));
    this->set_rotation(glm::vec3(glm::degrees(x), glm::degrees(y), glm::degrees(z)));

    // std::cout << "Rotation: " << rotation.getX() << ", " << rotation.getY() << ", " << rotation.getZ() << std::endl;
}

void PhysicsNode3D::update_scale()
{
    this->rigidBody->getCollisionShape()->setLocalScaling(btVector3(this->scale.x, this->scale.y, this->scale.z));
}