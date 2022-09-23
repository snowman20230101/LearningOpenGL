//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_TEXTUREPICTURE_2_H
#define LEARNINGOPENGL_1_TEXTUREPICTURE_2_H


#include "TexturePicture_1.h"

class TexturePicture_2 : public TexturePicture_1 {
public:
    TexturePicture_2();

    ~TexturePicture_2() override;

    int execute() override;

private:
    float textureVertices_2[32] = {
//            // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
//            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
//            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f  // top left
    };
};


#endif //LEARNINGOPENGL_1_TEXTUREPICTURE_2_H
