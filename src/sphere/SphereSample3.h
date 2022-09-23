//
// Created by windy on 2022/8/10.
//

#ifndef LEARNINGOPENGL_SPHERESAMPLE3_H
#define LEARNINGOPENGL_SPHERESAMPLE3_H

#include "Base.h"

#define sphereSample3VertexFile "sphere/sphere_sample3_vertex.glsl"
#define sphereSample3FragmentFile "sphere/sphere_sample3_fragment.glsl"

class SphereSample3 : public Base {
public:
    SphereSample3();

    ~SphereSample3() override;

    int execute() override;

private:

};


#endif //LEARNINGOPENGL_SPHERESAMPLE3_H
