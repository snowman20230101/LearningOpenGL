//
// Created by windy on 2021/12/20.
//

#ifndef LEARNINGOPENGL_1_GLMSAMPLE3D_H
#define LEARNINGOPENGL_1_GLMSAMPLE3D_H


#include "GLMSample.h"

#define glmVertex3DFileName "glm/texture_glm_sample3d_vertex.glsl"

class GLMSample3D : public GLMSample {
public:
    GLMSample3D();

    ~GLMSample3D() override;

    int execute() override;
};


#endif //LEARNINGOPENGL_1_GLMSAMPLE3D_H
