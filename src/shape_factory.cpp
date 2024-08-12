#include "user/shape_factory.h"

btConvexHullShape *ShapeFactory::createConvexHullShape(std::vector<Mesh> meshes)
{
    btConvexHullShape *convex_hull_shape = new btConvexHullShape();
    for (const auto &mesh : meshes)
    {
        for (const auto &vertex : mesh.vertices)
        {
            convex_hull_shape->addPoint(btVector3(vertex.Position.x, vertex.Position.y, vertex.Position.z));
        }
    }
    return convex_hull_shape;
}
btBvhTriangleMeshShape *ShapeFactory::createBvhTriangleMeshShape(std::vector<Mesh> meshes)
{
    btTriangleMesh *triangleMesh = new btTriangleMesh();
    for (const auto &mesh : meshes)
    {
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            btVector3 v0(mesh.vertices[mesh.indices[i]].Position.x, mesh.vertices[mesh.indices[i]].Position.y, mesh.vertices[mesh.indices[i]].Position.z);
            btVector3 v1(mesh.vertices[mesh.indices[i + 1]].Position.x, mesh.vertices[mesh.indices[i + 1]].Position.y, mesh.vertices[mesh.indices[i + 1]].Position.z);
            btVector3 v2(mesh.vertices[mesh.indices[i + 2]].Position.x, mesh.vertices[mesh.indices[i + 2]].Position.y, mesh.vertices[mesh.indices[i + 2]].Position.z);
            triangleMesh->addTriangle(v0, v1, v2);
        }
    }

    btBvhTriangleMeshShape *bvh_triangle_mesh_shape = new btBvhTriangleMeshShape(triangleMesh, true);
    return bvh_triangle_mesh_shape;
}
