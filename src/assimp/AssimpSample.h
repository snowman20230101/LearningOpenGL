//
// Created by windy on 2022/8/9.
//

#ifndef LEARNINGOPENGL_ASSIMPSAMPLE_H
#define LEARNINGOPENGL_ASSIMPSAMPLE_H

#include "Base.h"

#define assimpVertexFile "assimp/assimp_vertex.glsl"
#define assimpFragmentFile "assimp/assimp_fragment.glsl"


class AssimpSample : public Base {
public:
    AssimpSample();

    ~AssimpSample() override;

    int execute() override;

    void processInput(GLFWwindow *window) override;

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

private:
    std::string modelPath;
};


#endif //LEARNINGOPENGL_ASSIMPSAMPLE_H
