//
// Created by windy on 2021/12/15.
//

#ifndef LEARNINGOPENGL_1_UTILS_H
#define LEARNINGOPENGL_1_UTILS_H

#include <string>
#include "CommonInclude.h"

using namespace std;

class Utils {
public:
    /**
     * 加载文件
     *
     * @param fileName
     * @param source
     * @return
     */
    static bool loadFile(const char *fileName, string &source);

    /**
     * 创建并加载一个纹理
     *
     * @param path
     * @param alpha
     * @return
     */
    static GLuint loadTexture(const char *path, GLboolean alpha = GL_FALSE);
};


#endif //LEARNINGOPENGL_1_UTILS_H
