//
// Created by windy on 2022/7/13.
//

#ifndef LEARNINGOPENGL_TRIANGLEEXERCISES_2_H
#define LEARNINGOPENGL_TRIANGLEEXERCISES_2_H

#include "Triangle.h"

class TriangleExercises_2 : public Triangle {
public:
    TriangleExercises_2();

    ~TriangleExercises_2() override;

    int execute() override;

private:
    // 一行为一个顶点（前三个为具体的一个点，后三个是这个点的颜色）
    float vertexIds[18] = {
            -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Left
            -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Right
            -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // Top
    };

    float vertexIds2[18] = {
            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Left
            0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Right
            0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f // Top
    };
};


#endif //LEARNINGOPENGL_TRIANGLEEXERCISES_2_H
