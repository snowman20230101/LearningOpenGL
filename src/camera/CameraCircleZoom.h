//
// Created by windy on 2021/12/21.
//

#ifndef LEARNINGOPENGL_1_CAMERACIRCLEZOOM_H
#define LEARNINGOPENGL_1_CAMERACIRCLEZOOM_H

#include "CameraCircleKeyboard_dt.h"

static float yaw = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
static float pitch = 0.0f;
static float fov = 45.0f;

class CameraCircleZoom : public CameraCircleKeyboard_dt {
public:

    CameraCircleZoom();

    ~CameraCircleZoom() override;

    int execute() override;

    void processInput(GLFWwindow *window) override;

    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
};


#endif //LEARNINGOPENGL_1_CAMERACIRCLEZOOM_H
