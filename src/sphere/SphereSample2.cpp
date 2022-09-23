//
// Created by windy on 2022/8/10.
// 绘制球体(第二种方式生成球体顶点坐标)
//

#include "SphereSample2.h"

#include <vector>

void createSphere(GLfloat *sphere, GLuint Longitude, GLuint Latitude);

SphereSample2::SphereSample2() {
    std::cout << "SphereSample2::SphereSample2()" << std::endl;
}

SphereSample2::~SphereSample2() {
    std::cout << "SphereSample2::~SphereSample2()" << std::endl;
}

int SphereSample2::execute() {
    std::cout << "SphereSample::execute()" << std::endl;

    createWindow();

    glfwSetScrollCallback(pWindow, scrollCallback);
    glfwSetCursorPosCallback(pWindow, mouseCallback);

    GLuint programId = createGLProgram(sphereSample2VertexFile, sphereSample2FragmentFile);

    GLuint lats = 50;
    GLuint lons = 50;
    GLfloat vertices[6 * 3 * lats * lons];
    std::cout << "total:" << sizeof(vertices) << std::endl;
    createSphere(vertices, lons, lats);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(pWindow)) {
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        processInput(pWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);

        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 view;
        glm::mat4 projection;
        // 旋转
//        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, (GLfloat) glfwGetTime() * glm::radians(60.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        // 位移
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.5f));

        // 投影矩阵
        projection = glm::perspective(glm::radians(90.0f), (GLfloat) SRC_WIDTH / (GLfloat) SRC_HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // 开启面剔除(只需要展示一个面，否则会有重合)
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 6 * lats * lons);
//        glDrawArrays(GL_POINTS, 0, 6 * lats * lons);
//        glDrawArrays(GL_TRIANGLES, 0, 6 * lats * lons);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programId);

    glfwTerminate();
    return 0;
}

void SphereSample2::processInput(GLFWwindow *window) {
//    std::cout << "Base processInput() " << std::endl;
    // ESC 推出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // 键盘
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void SphereSample2::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((GLfloat) yoffset);
}

void SphereSample2::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (GLfloat) xpos;
        lastY = (GLfloat) ypos;
        firstMouse = false;
    }

    GLfloat xoffset = (GLfloat) xpos - lastX;
    GLfloat yoffset = lastY - (GLfloat) ypos;

    lastX = (GLfloat) xpos;
    lastY = (GLfloat) ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

glm::vec3 getPoint(GLfloat u, GLfloat v) {
    GLfloat r = 0.9f;
    GLfloat pi = glm::pi<GLfloat>();
    GLfloat z = r * std::cos(pi * u);
    GLfloat x = r * std::sin(pi * u) * std::cos(2 * pi * v);
    GLfloat y = r * std::sin(pi * u) * std::sin(2 * pi * v);
    return glm::vec3(x, y, z);
}


void createSphere(GLfloat *sphere, GLuint Longitude, GLuint Latitude) {
    // Longitude：经线切分个数
    // Latitude：纬线切分个数
    GLfloat lon_step = 1.0f / Longitude;
    GLfloat lat_step = 1.0f / Latitude;
    GLuint offset = 0;
    for (int lat = 0; lat < Latitude; lat++) {  // 纬线u
        for (int lon = 0; lon < Longitude; lon++) { // 经线v
            // 一次构造4个点，两个三角形，
            glm::vec3 point1 = getPoint(lat * lat_step, lon * lon_step);
            glm::vec3 point2 = getPoint((lat + 1) * lat_step, lon * lon_step);
            glm::vec3 point3 = getPoint((lat + 1) * lat_step, (lon + 1) * lon_step);
            glm::vec3 point4 = getPoint(lat * lat_step, (lon + 1) * lon_step);
            memcpy(sphere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
            offset += 3;
            memcpy(sphere + offset, glm::value_ptr(point4), 3 * sizeof(GLfloat));
            offset += 3;
            memcpy(sphere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
            offset += 3;

            memcpy(sphere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
            offset += 3;
            memcpy(sphere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
            offset += 3;
            memcpy(sphere + offset, glm::value_ptr(point2), 3 * sizeof(GLfloat));
            offset += 3;
        }
    }
    // std::cout<<"offset:" << offset << std::endl;
}




