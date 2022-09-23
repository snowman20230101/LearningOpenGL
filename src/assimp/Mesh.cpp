//
// Created by windy on 2022/8/9.
//

#include <sstream>
#include <utility>
#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture)
        : vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(texture)) {
    this->setupMesh();
}

void Mesh::draw(GLuint programId) {
    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding // 在绑定纹理前需要激活适当的纹理单元
        // Retrieve texture number (the N in diffuse_textureN)
        // 检索纹理序列号 (N in diffuse_textureN)
        stringstream ss;
        string number;
        string name = this->textures[i].type;
        if (name == "texture_diffuse")
            ss << diffuseNr++; // Transfer GLuint to stream // 将GLuin输入到string stream
        else if (name == "texture_specular")
            ss << specularNr++; // Transfer GLuint to stream // 将GLuin输入到string stream
        number = ss.str();
        // Now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(programId, (name + number).c_str()), i);
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, this->textures[i].textureId);
    }

    // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
    glUniform1f(glGetUniformLocation(programId, "material.shininess"), 16.0f);

    // Draw mesh
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    // 一个预处理指令叫做offsetof(s,m)把结构体作为它的第一个参数，第二个参数是这个结构体名字的变量。这是结构体另外的一个重要用途。函数返回这个变量从结构体开始的字节偏移量（offset）
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}