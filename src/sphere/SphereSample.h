//
// Created by windy on 2022/8/10.
// 绘制球体
//

#ifndef LEARNINGOPENGL_SPHERESAMPLE_H
#define LEARNINGOPENGL_SPHERESAMPLE_H

#include "Base.h"

#define sphereSampleVertexFile "sphere/sphere_sample_vertex.glsl"
#define sphereSampleFragmentFile "sphere/sphere_sample_fragment.glsl"

class SphereSample : public Base {
public:
    SphereSample();

    ~SphereSample() override;

    int execute() override;

private:

};


#endif //LEARNINGOPENGL_SPHERESAMPLE_H
