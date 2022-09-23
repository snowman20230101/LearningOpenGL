//
// Created by windy on 2021/12/15.
//

#include "Utils.h"
#include <filesystem>
#include <fstream>

bool Utils::loadFile(const char *fileName, string &source) {
    source.clear();
    std::ifstream in_stream(fileName);
    if (!in_stream) {
        return false;
    }

    source.assign(std::istreambuf_iterator<char>(in_stream), std::istreambuf_iterator<char>());
    return true;
}

GLuint Utils::loadTexture(const char *path, GLboolean alpha) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 纹理环绕
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);

    // 纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    unsigned char *image = stbi_load(path, &width, &height, &channels, 0);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     alpha ? GL_RGBA : GL_RGB,
                     width,
                     height,
                     0,
                     alpha ? GL_RGBA : GL_RGB,
                     GL_UNSIGNED_BYTE,
                     image
        );
        // glGenerateMipmap- 为纹理对象生成一组完整的mipmap
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    return textureID;
}