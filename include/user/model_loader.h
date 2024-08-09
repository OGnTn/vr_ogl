#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb/stb_image_write.h"

#include "user/mesh.h"

class ModelLoader
{
public:
    static void load_model(std::string file_path, std::vector<Mesh> &meshes);
    static void process_node(aiNode *node, const aiScene *scene, std::vector<Mesh> &meshes, std::vector<std::string> &materials_loaded, const aiMatrix4x4 &parent_transformation);

    static Mesh process_mesh(aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 &node_transformation, std::vector<std::string> &materials_loaded);
    static std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string type_name, const aiScene *scene);
};
#endif