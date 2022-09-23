//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_TEXTUREPICTURE_1_H
#define LEARNINGOPENGL_1_TEXTUREPICTURE_1_H

#include "TexturePicture.h"

#define textureFragFileName_1 "texture/texture_fragment_1.glsl"

class TexturePicture_1 : public TexturePicture {
public:
    TexturePicture_1();

    ~TexturePicture_1() override;

    int execute() override;
};


#endif //LEARNINGOPENGL_1_TEXTUREPICTURE_1_H
