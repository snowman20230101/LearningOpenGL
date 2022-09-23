//
// Created by windy on 2022/8/10.
//

#ifndef LEARNINGOPENGL_SPHERESAMPLE2_H
#define LEARNINGOPENGL_SPHERESAMPLE2_H


#include "Base.h"

#define sphereSample2VertexFile "sphere/sphere_sample2_vertex.glsl"
#define sphereSample2FragmentFile "sphere/sphere_sample2_fragment.glsl"

class SphereSample2 : public Base {
public:
    SphereSample2();

    ~SphereSample2() override;

    int execute() override;

    void processInput(GLFWwindow *window) override;

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);


private:

};


#endif //LEARNINGOPENGL_SPHERESAMPLE2_H
