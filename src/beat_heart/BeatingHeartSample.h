//
// Created by windy on 2022/8/5.
//

#ifndef LEARNINGOPENGL_BEATINGHEARTSAMPLE_H
#define LEARNINGOPENGL_BEATINGHEARTSAMPLE_H

#include "CommonInclude.h"
#include "Base.h"

#define beatingHeartVertexFile "beat_heart/beatingheart_vertex.glsl"
#define beatingHeartFragmentFile "beat_heart/beatingheart_fragment.glsl"

class BeatingHeartSample : public Base {
public:

    BeatingHeartSample();

    ~BeatingHeartSample() override;

    int execute() override;

private:
    virtual void updateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);

private:
    // 顶点数据
    GLfloat verticesCoords[12] = {
            -1.0f, 1.0f, 0.0f,  // Position 0 左上
            -1.0f, -1.0f, 0.0f,  // Position 1 左下
            1.0f, -1.0f, 0.0f,  // Position 2 又下
            1.0f, 1.0f, 0.0f,  // Position 3 // 右上
    };

    // 纹理坐标
    GLfloat textureCoords[8] = {
            0.0f, 0.0f,        // TexCoord 0 左下
            0.0f, 1.0f,        // TexCoord 1 左上
            1.0f, 1.0f,        // TexCoord 2 右上
            1.0f, 0.0f         // TexCoord 3 右下
    };

    // 绘制元素
    GLushort indices[6] = {0, 1, 2, 0, 2, 3};

    int m_AngleX = 0;
    int m_AngleY = 0;
    float m_ScaleX = 0;
    float m_ScaleY = 0;

    // 用于顶点着色器
    glm::mat4 m_MVPMatrix{};

    // 矩阵
    GLint m_MVPMatLoc = GL_NONE;
    // 时间
    GLint m_TimeLoc = GL_NONE;
    // 大小
    GLint m_SizeLoc = GL_NONE;
};


#endif //LEARNINGOPENGL_BEATINGHEARTSAMPLE_H
