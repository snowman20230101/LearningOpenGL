//
// Created by windy on 2022/7/13.
//

#ifndef LEARNINGOPENGL_TRIANGLEEXERCISES_3_H
#define LEARNINGOPENGL_TRIANGLEEXERCISES_3_H

#include "Triangle.h"

// 三角形
#define triangleExercises_3_VertexFile "triangle/triangleExercises_3_vertex.glsl"
#define triangleExercises_3_FragmentFile "triangle/triangleExercises_3_fragment.glsl"
#define triangleExercises_3_FragmentFile2 "triangle/triangleExercises_3_fragment2.glsl"

class TriangleExercises_3 : public Triangle {
public:
    TriangleExercises_3();

    ~TriangleExercises_3() override;

    int execute() override;

private:
    // 一行为一个顶点（前三个为具体的一个点，后三个是这个点的颜色）
    float vertexIds[9] = {
            -0.9f, -0.5f, 0.0f,   // Left
            -0.0f, -0.5f, 0.0f,   // Right
            -0.45f, 0.5f, 0.0f    // Top
    };

    float vertexIds2[9] = {
            0.0f, -0.5f, 0.0f,  // Left
            0.9f, -0.5f, 0.0f,  // Right
            0.45f, 0.5f, 0.0f   // Top
    };
};

#endif //LEARNINGOPENGL_TRIANGLEEXERCISES_3_H
