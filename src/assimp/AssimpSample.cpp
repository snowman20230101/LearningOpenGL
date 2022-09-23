//
// Created by windy on 2022/8/9.
//

#include "AssimpSample.h"
#include "Model.h"

AssimpSample::AssimpSample() {
    std::cout << "AssimpSample::AssimpSample()" << std::endl;
//    modelPath = std::string(ROOT_DIR) + "resources/objects/backpack/backpack.obj";
//    modelPath = std::string(ROOT_DIR) + "resources/objects/cyborg/cyborg.obj";
    modelPath = std::string(ROOT_DIR) + "resources/objects/nanosuit/nanosuit.obj";
//    modelPath = std::string(ROOT_DIR) + "resources/objects/planet/planet.obj";
//    modelPath = std::string(ROOT_DIR) + "resources/objects/rock/rock.obj";
}

AssimpSample::~AssimpSample() {
    std::cout << "AssimpSample::~AssimpSample()" << std::endl;
}

int AssimpSample::execute() {
    std::cout << "AssimpSample::~execute()" << std::endl;

    createWindow();

    glfwSetCursorPosCallback(pWindow, mouseCallback);
    glfwSetScrollCallback(pWindow, scrollCallback);

    glEnable(GL_DEPTH_TEST);

    GLuint programId = createGLProgram(assimpVertexFile, assimpFragmentFile);
    Model ourModel(modelPath.c_str());

    while (!glfwWindowShouldClose(pWindow)) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        processInput(pWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);

        // Transformation matrices
        glm::mat4 projection = glm::perspective(camera.Zoom, (float) SRC_WIDTH / (float) SRC_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model;
        // Translate it down a bit so it's at the center of the scene
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        // It's a bit too big for our scene, so scale it down
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ourModel.draw(programId);

        glfwSwapBuffers(pWindow);
    }

    glDisable(GL_DEPTH_TEST);

    glfwTerminate();
    return 0;
}

void AssimpSample::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void AssimpSample::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((GLfloat) yoffset);
}

void AssimpSample::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
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