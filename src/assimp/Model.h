//
// Created by windy on 2022/8/9.
// 模型 结构体
//

#ifndef LEARNINGOPENGL_MODEL_H
#define LEARNINGOPENGL_MODEL_H

#include "CommonInclude.h"
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


class Model {
public:
    /*  成员函数   */
    explicit Model(const GLchar *path) {
        this->loadModel(path);
    }

    void draw(GLuint programId);

private:
    /*  模型数据  */
    vector<Mesh> meshes;
    std::string directory;
    vector<Texture> textures_loaded;    // Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    /*  私有成员函数   */
    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    GLint textureFromFile(const char *path, string directory);
};


#endif //LEARNINGOPENGL_MODEL_H
