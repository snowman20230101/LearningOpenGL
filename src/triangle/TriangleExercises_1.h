//
// Created by windy on 2022/7/12.
// 通过 VAO VBO 画两个三角心
// 练习题：添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
//

#ifndef LEARNINGOPENGL_TRIANGLEEXERCISES_1_H
#define LEARNINGOPENGL_TRIANGLEEXERCISES_1_H

#include "Triangle.h"

class TriangleExercises_1 : public Triangle {

public:
    TriangleExercises_1();

    ~TriangleExercises_1() override;

    int execute() override;

private:
    // 一行为一个顶点（前三个为具体的一个点，后三个是这个点的颜色）
    float vertexIds[36] = {
            -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Left
            -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Right
            -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Top
            // Second triangle
            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Left
            0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Right
            0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Top
    };
};


#endif //LEARNINGOPENGL_TRIANGLEEXERCISES_1_H
