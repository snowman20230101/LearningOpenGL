//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_TRIANGLE_H
#define LEARNINGOPENGL_1_TRIANGLE_H

#include "Base.h"

// 三角形
#define triangleVertexFile "triangle/triangle_vertex.glsl"
#define triangleFragmentFile "triangle/triangle_fragment.glsl"

class Triangle : public Base {
public:

    Triangle();

    ~Triangle() override;

    int execute() override;

private:
    float triangleVertices[18] = {
            // 前三个是 顶点 ，后三个是 颜色
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
    };
};

#endif //LEARNINGOPENGL_1_TRIANGLE_H
