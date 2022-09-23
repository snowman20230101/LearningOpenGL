//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_TRIANGLE_1_H
#define LEARNINGOPENGL_1_TRIANGLE_1_H

#include "Triangle.h"

class Triangle2 : public Triangle {
public:
    Triangle2();

    ~Triangle2() override;

    int execute() override;

private:
    /*
    float triangle_1Vertices[36] = {
            -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            -0.0f, -0.5f, 0.0, 0.0f, 1.0f, 0.0f,// right
            -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top
            0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // left
            0.9f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,// right
            0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f  // top};
    };
     */

    // 四边形，也就是两个三角形 TODO 这里我们可以注意到，两个三角形用了四个点。因为有两个点是重合点，可以复用，不管你怎么画菱形对角线是重合两个点的
    float triangle_1Vertices[24] = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
//            0.5f, -0.5f, 0.0, 0.0f, 1.0f, 0.0f,// bottom right
//            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,// bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f  // top left
    };


    // 一个三角形
    float triangle_1Vertices2[18] = {
            0.8f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, // left
            1.0f, -1.0f, 0.0f, 0.1f, 0.1f, 0.1f,// right
            1.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f  // top
    };

    unsigned int indices[6] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };
};

#endif //LEARNINGOPENGL_1_TRIANGLE_1_H