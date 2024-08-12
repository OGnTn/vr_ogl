#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include "user/mesh.h"

class ShapeFactory
{
public:
    static btConvexHullShape *createConvexHullShape(std::vector<Mesh> meshes);
    static btBvhTriangleMeshShape *createBvhTriangleMeshShape(std::vector<Mesh> meshes);
};

#endif