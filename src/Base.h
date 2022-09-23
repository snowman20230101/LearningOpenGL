//
// Created by windy on 2021/12/16.
//

#ifndef LEARNINGOPENGL_1_BASE_H
#define LEARNINGOPENGL_1_BASE_H

#include "CommonInclude.h"
#include "camera.h"


/**
 * TODO
 * 投影矩阵
 *      正交投影矩阵: glm::ortho(float left, float right, float bottom, float top, float zNear, float zFar);
 *      透视投影矩阵: glm::perspective(float fovy, float aspect, float zNear, float zFar);
 * 向量的乘法
 *      向量的叉乘: glm::cross(vector1,vector2)
 *      向量的点乘: glm::dot(vector1,vector2)
 * 基础函数:
 * glm::value_ptr(): 传入一个矩阵，返回一个数组，从左到右按列优先。
 * glm::normalize(vector) : 向量的单位化（保持其方向不变，将其长度化为1）.
                            可以normalize 一个运算式赋值，直接normalize(a)但不赋值，不能normlize单个向量，然后赋值给其他向量:
                            // 可以这样使用：
                            glm::vec3 a = { 3.0, 2.0, 3.0 };
                            glm::vec3 b = { 1.0, 0.0, 3.0 };
                            glm::vec3 c = glm::normalize(a*b);
                            // 或者：
                            glm::normalize(a); // 直接单位化，这里直接修改了参数a
                            // 但不能这么使用：
                            glm::vec3 b=glm::normalize(c);

 * glm::radians() 角度制转弧度制，可应用于glm::rotate()中。
 * glm::translate() : 返回一个平移矩阵，第一个参数是目标矩阵，第二个参数是平移的方向向量。
 * glm::rotate() : 返回一个将点绕某个轴逆时针旋转一定弧度的旋转矩阵，第一个参数是目标矩阵，第二个参数是弧度，第三个参数是旋转轴。
 * glm::scale() : 返回一个缩放矩阵，第一个参数是目标矩阵，第二个参数是在各坐标轴上的缩放系数。
 *
 */

static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// timing
static float deltaTime = 0.0f;    // time between current frame and last frame
static float lastFrame = 0.0f;

static GLfloat lastX = 400, lastY = 300;
static bool firstMouse = true;

class Base {
public:

    Base();

    virtual ~Base();

    virtual int execute();

    virtual bool createWindow();

    virtual unsigned int createGLProgram(const char *vertFileName,
                                         const char *fragFileName,
                                         const char *geometryFileName = ""
    );

    virtual void processInput(GLFWwindow *window);

    static void framebufferSizeCallback(GLFWwindow *window, int w, int h);

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

protected:
    GLFWwindow *pWindow{};
};

#endif //LEARNINGOPENGL_1_BASE_H
