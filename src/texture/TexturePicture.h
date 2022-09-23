//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_TEXTUREPICTURE_H
#define LEARNINGOPENGL_1_TEXTUREPICTURE_H

#include "Base.h"

#define textureVertexFileName "texture/texture_vertex.glsl"
#define textureFragFileName "texture/texture_fragment.glsl"
#define textureFragFileName1 "texture/texture_fenping_fragment.glsl"

class TexturePicture : public Base {
public:
    TexturePicture();

    ~TexturePicture() override;

    int execute() override;

protected:
    float textureVertices[32] = {
            // positions          // colors           // texture coords  // 反转纹理 Y 轴
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right           1.0f, 0.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right   1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left 0.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left   0.0f, 0.0f,
    };

    unsigned int  textureIndices [6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
};

#endif //LEARNINGOPENGL_1_TEXTUREPICTURE_H
