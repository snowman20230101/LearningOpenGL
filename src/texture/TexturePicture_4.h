//
// Created by windy on 2021/12/17.
//

#ifndef LEARNINGOPENGL_1_TEXTUREPICTURE_4_H
#define LEARNINGOPENGL_1_TEXTUREPICTURE_4_H

#include "TexturePicture.h"

#define textureFragFileName_4 "texture/texture_fragment_4.glsl"

class TexturePicture_4 : public TexturePicture {
public:
    TexturePicture_4();

    ~TexturePicture_4() override;

    int execute() override;

private:
    float mMixValue{0.2f};
};


#endif //LEARNINGOPENGL_1_TEXTUREPICTURE_4_H
