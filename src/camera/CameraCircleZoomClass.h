//
// Created by windy on 2021/12/21.
//

#ifndef LEARNINGOPENGL_1_CAMERACIRCLEZOOMCLASS_H
#define LEARNINGOPENGL_1_CAMERACIRCLEZOOMCLASS_H

#include "CameraCircleZoom.h"

class CameraCircleZoomClass : public CameraCircleZoom {
public:

    int execute() override;

    void processInput(GLFWwindow *window) override;

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);
};

#endif //LEARNINGOPENGL_1_CAMERACIRCLEZOOMCLASS_H
