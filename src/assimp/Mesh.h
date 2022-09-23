//
// Created by windy on 2022/8/9.
// 网格结构体
//

#ifndef LEARNINGOPENGL_MESH_H
#define LEARNINGOPENGL_MESH_H

#include <vector>

#include "CommonInclude.h"

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture);

    void draw(GLuint programId);

public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
private:
    GLuint VAO{GL_NONE}, VBO{GL_NONE}, EBO{GL_NONE};

    void setupMesh();
};


#endif //LEARNINGOPENGL_MESH_H
