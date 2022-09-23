//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_TEXTUREPICTURE_3_H
#define LEARNINGOPENGL_1_TEXTUREPICTURE_3_H


#include "TexturePicture.h"

#define textureFragFileName_3 "texture/texture_fragment_3.glsl"


class TexturePicture_3 : public TexturePicture {
public:
    int execute() override;
private:
    float textureVertices_3[32] = {
            // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left
    };
};

#endif //LEARNINGOPENGL_1_TEXTUREPICTURE_3_H
