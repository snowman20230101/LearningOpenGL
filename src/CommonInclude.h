//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_COMMONINCLUDE_H
#define LEARNINGOPENGL_1_COMMONINCLUDE_H

#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>
//#include <glut.h>

// openGL 数学
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#common <glew.h> // 倒入 <glad/glad.h> 这个头文件 就不用倒入 <glew.h>。
// 这是glad 的约束，或者是规范。这个如同Java中的import javax.microedition.khronos.egl.EGLConfig;。这是厂商具体定义的。

#include "Utils.h"
#include "stb_image.h"
#include "filesystem.h"

#include <assimp/types.h>

#define SRC_WIDTH 960
#define SRC_HEIGHT 640
#define LEARN_TITLE "Learning OpenGL"
#define ROOT_DIR "/Users/windy/devlop/opengl/code/LearningOpenGL/"
#define RAW "/Users/windy/devlop/opengl/code/LearningOpenGL/raw/"

//const char *vertexShaderSource =
//        "attribute vec3 aPos;\n"
//        "void main(){\n"
//        "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//        "}\n\0";
//
//const char *fragmentShaderSource =
//        "void main(){\n"
//        "   gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
//        "}\n\0";

// 一个网格应该至少需要一组顶点，每个顶点包含一个位置向量，一个法线向量，一个纹理坐标向量。一个网格也应该包含一个索引绘制用的索引，以纹理（diffuse/specular map）形式表现的材质数据。
struct Vertex {
    glm::vec3 Position; // 位置向量
    glm::vec3 Normal; // 法线向量
    glm::vec2 TexCoords; // 纹理坐标向量
};

struct Texture {
    GLuint textureId;
    std::string type;
    aiString path;
};

#endif //LEARNINGOPENGL_1_COMMONINCLUDE_H
