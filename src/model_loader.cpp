#include "user/model_loader.h"

void ModelLoader::load_model(std::string file_path, std::vector<Mesh> &meshes)
{
    Assimp::Importer importer;
    std::vector<std::string> materials_loaded;
    const aiScene *scene = importer.ReadFile(file_path, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    aiMatrix4x4 identity_matrix; // Identity matrix for root node
    process_node(scene->mRootNode, scene, meshes, materials_loaded, identity_matrix);
}

void ModelLoader::process_node(aiNode *node, const aiScene *scene, std::vector<Mesh> &meshes, std::vector<std::string> &materials_loaded, const aiMatrix4x4 &parent_transformation)
{
    aiMatrix4x4 node_transformation = parent_transformation * node->mTransformation;

    std::cout << "Processing node: " << node->mName.C_Str() << std::endl;
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene, node_transformation, materials_loaded));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene, meshes, materials_loaded, node_transformation);
    }
}
glm::mat4 aiMatrixToGlm(const aiMatrix4x4 &aiMat)
{
    return glm::mat4(
        aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1,
        aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
        aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
        aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4);
}

void apply_transform(glm::vec3 &vertex, const aiMatrix4x4 &transformation)
{
    // Convert aiMatrix4x4 to glm::mat4
    glm::mat4 glm_transform = aiMatrixToGlm(transformation);

    // Convert glm::vec3 to glm::vec4 (homogeneous coordinates)
    glm::vec4 temp(vertex, 1.0f);

    // Apply transformation
    glm::vec4 transformed = glm_transform * temp;

    // Convert back to glm::vec3
    vertex = glm::vec3(transformed);
}

Mesh ModelLoader::process_mesh(aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 &node_transformation, std::vector<std::string> &materials_loaded)
{
    std::cout << "Processing mesh: " << mesh->mName.C_Str() << std::endl;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    aiMatrix4x4 mesh_transform = node_transformation;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        apply_transform(vector, mesh_transform);
        vertex.Position = vector;

        if (mesh->mNormals)
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            apply_transform(vector, mesh_transform);
            vertex.Normal = vector;
        }

        for (unsigned int j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; j++)
        {
            if (mesh->mTextureCoords[j])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[j][i].x;
                vec.y = mesh->mTextureCoords[j][i].y;
                vertex.TexCoords = vec;
                break; // Use the first available set
            }
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        unsigned int diffuse_count = material->GetTextureCount(aiTextureType_DIFFUSE);
        if (diffuse_count)
        {
            aiString texture_file;
            material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texture_file);
            if ('*' != texture_file.data[0])
            {
                // if the path contains "/", assume it is an absolute path
                if (strchr(texture_file.C_Str(), '/') != NULL)
                {
                    std::cout << "external texture" << std::endl;
                    std::cout << texture_file.C_Str() << std::endl;
                    Texture tex(texture_file.C_Str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
                    textures.push_back(tex);
                }
                else
                {
                    // relative filename. look for it in ../res/textures/
                    std::string texture_path = "../res/textures/";
                    texture_path += texture_file.C_Str();
                    std::cout << "internal texture" << std::endl;
                    Texture tex(texture_path.c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
                    textures.push_back(tex);
                }
            }
            else
            {
                // internal texture
                std::cout << "internal texture" << std::endl;
                unsigned int path = atoi(texture_file.C_Str() + 1);
                aiTexture *t = scene->mTextures[path];
                if (t->mHeight == 0)
                {
                    // compressed texture
                    aiTexel *texel = t->pcData;
                    unsigned char *rawData = reinterpret_cast<unsigned char *>(texel);

                    int width, height, nrChannels;
                    stbi_info_from_memory(rawData, t->mWidth, &width, &height, &nrChannels);

                    unsigned char *img = stbi_load_from_memory(rawData, t->mWidth, &width, &height, &nrChannels, 3);
                    Texture tex(img, width, height, nrChannels, "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
                    stbi_image_free(img);
                    textures.push_back(tex);
                }
                else
                {
                    // uncompressed texture
                    Texture tex((unsigned char *)t->pcData, t->mWidth, t->mHeight, 3, "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
                    textures.push_back(tex);
                }
            }
        }
        materials_loaded.push_back(material->GetName().C_Str());
    }

    return Mesh(vertices, indices, textures);
}
