//
// Created by windy on 2022/8/11.
//

#ifndef LEARNINGOPENGL_SPHERELIGHTSAMPLE_H
#define LEARNINGOPENGL_SPHERELIGHTSAMPLE_H

#include "Base.h"

#define sphereLightSampleVertexFile "sphere/sphere_light_sample_vertex.glsl"
#define sphereLightSampleFragmentFile "sphere/sphere_light_sample_fragment.glsl"

class SphereLightSample : public Base {
public:
    SphereLightSample();

    ~SphereLightSample() override;

    int execute() override;

private:

};

#endif //LEARNINGOPENGL_SPHERELIGHTSAMPLE_H
