//
// Created by windy on 2021/12/17.
//

#ifndef LEARNINGOPENGL_1_GLMSAMPLE_H
#define LEARNINGOPENGL_1_GLMSAMPLE_H


#include "TexturePicture.h"

#define glmVertexFileName "glm/texture_glm_sample_vertex.glsl"
#define glmFragmentFileName "glm/texture_glm_sample_fragment.glsl"


class GLMSample : public TexturePicture {
public:
    GLMSample();

    ~GLMSample() override;

    int execute() override;

private:
    float mMixValue{0.2f};
};


#endif //LEARNINGOPENGL_1_GLMSAMPLE_H
