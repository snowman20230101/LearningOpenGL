//
// Created by windy on 2021/12/16.
//

#include "Base.h"

/**
 * 打印 基本类型字节占位
 *
 * @return
 */
int testSizeOf() {
    printf("基本类型字节占位:\n");
    std::cout << "  size of char:" << sizeof(char) << std::endl;
    std::cout << "  size of short:" << sizeof(short) << std::endl;
    std::cout << "  size of int:" << sizeof(int) << std::endl;
    std::cout << "  size of long:" << sizeof(long) << std::endl;
    std::cout << "  size of long long:" << sizeof(long long) << std::endl;
    std::cout << "  size of double:" << sizeof(double) << std::endl;
    std::cout << "  size of float:" << sizeof(float) << std::endl;
    std::cout << "  size of bool:" << sizeof(bool) << std::endl;
    std::cout << "  size of string:" << sizeof(std::string) << std::endl;
    std::cout << "  size of u_int:" << sizeof(u_int) << std::endl;
    std::cout << "  size of unsigned int:" << sizeof(unsigned long) << std::endl;
    printf("print bit finish. \n\n");
    return 0;
}

Base::Base() {
    testSizeOf();
    std::cout << "Base::Base()" << std::endl;
}

Base::~Base() {
    std::cout << "Base::~Base()" << std::endl;
}

bool Base::createWindow() {
    int glfw = glfwInit();
    if (glfw == GLFW_FALSE) {
        std::cout << "Failed called glfwInit" << std::endl;
        throw new std::exception();
    }

    std::cout << "Start OpenGL core profile version 3.3" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式(无序向后兼容性)
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 不可改变窗口大小

//
// ------------------------------
#ifdef __APPLE__
    // uncomment this statement to fix compilation on OS X 取消注释此语句以修复OS X上的编译
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // 创建窗口
    // ------------------------------
    GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, LEARN_TITLE, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();// 销毁
        throw new std::exception();
    }

    pWindow = window;

    // 窗口绑定 glContext
    // ------------------------------
    glfwMakeContextCurrent(window); // 将窗口的上下文设置为当前进程的主上下文
    glfwSetFramebufferSizeCallback(window, Base::framebufferSizeCallback); // std::bind
//    std::bind()

    // glad: load all OpenGL function pointers
    // 初始化GLAD，加载OpenGL指针地址的函数
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw new std::exception();
    }

    int windowWidth, windowHeight;
    glfwGetWindowSize(pWindow, &windowWidth, &windowHeight);
    printf("create window success. windowWidth=%d, windowHeight=%d\n\n", windowWidth, windowHeight);
    return true;
}

unsigned int Base::createGLProgram(const char *vertFileName, const char *fragFileName, const char *geometryFileName) {
    // 顶点着色器
    // 创建着色器程序
    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexSource;
    std::string fileName = std::string(RAW) + std::string(vertFileName);
    Utils::loadFile(fileName.c_str(), vertexSource);
    const char *vertexChar = vertexSource.c_str();

    // 加载着色器程序
    glShaderSource(vertexShaderId, 1, &vertexChar, NULL);

    // 编译着色器
    glCompileShader(vertexShaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        glDeleteShader(vertexShaderId);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 片段着色器
    success = 0;
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentSource;
    fileName = std::string(RAW) + std::string(fragFileName);
    Utils::loadFile(fileName.c_str(), fragmentSource);
    const char *fragmentChar = fragmentSource.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentChar, NULL);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        glDeleteShader(fragmentShaderId);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint geometryShaderId = -1;

    // 几个着色器
    bool hasGeometryShader = false;
    if (strlen(geometryFileName) > 0) {

        geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
        std::string geometrySource;
        fileName = std::string(RAW) + std::string(geometryFileName);
        Utils::loadFile(fileName.c_str(), geometrySource);
        const char *geometryChar = geometrySource.c_str();
        glShaderSource(geometryShaderId, 0, &geometryChar, NULL);
        glCompileShader(geometryShaderId);
        glGetShaderiv(geometryShaderId, GL_GEOMETRY_SHADER, &success);

        if (!success) {
            glGetShaderInfoLog(geometryShaderId, 512, NULL, infoLog);
            glDeleteShader(geometryShaderId);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            hasGeometryShader = true;
        }
    }

    // 程序
    success = 0;
    // 创建 gpu 程序
    unsigned int programId = glCreateProgram();
    // 绑定 着色器
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    if (hasGeometryShader) {
        glAttachShader(programId, geometryShaderId);
    }

    // 链接 gpu 程序
    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        glDeleteProgram(programId);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    printf("Base::createGLProgram() vertexShaderId=%d, fragmentShaderId=%d, geometryShaderId=%d, programId=%d\n",
           vertexShaderId,
           fragmentShaderId,
           geometryShaderId,
           programId
    );

    // 创建 gpu程序后，两个着色器，已经无用了，可以解绑，删除了。
    glDetachShader(programId, vertexShaderId);
    glDeleteShader(vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(fragmentShaderId);

    if (hasGeometryShader) {
        glDetachShader(programId, geometryShaderId);
        glDeleteShader(geometryShaderId);
    }

    return programId;
}

int Base::execute() {
    std::cout << "Base::execute()" << std::endl;

    createWindow();

    // render loop
    // ------------------------------
    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();
        // input
        processInput(pWindow);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.) 交换数据
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(pWindow);
    }

    glfwTerminate();
    return 0;
}

void Base::processInput(GLFWwindow *window) {
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

void Base::framebufferSizeCallback(GLFWwindow *window, int w, int h) {
//    std::cout << "Base framebufferSizeCallback() w=" << w + ", h=" << h << std::endl;
//    // make sure the viewport matches the new window dimensions; note that width and
//    // height will be significantly larger than specified on retina displays.
    // openGL 中的glViewPort 官方定义为，视口变换。
    // 意思是将已经通过透视除法转换为归一化的坐标的相应数据，转化到具体的屏幕（窗口）坐标。
    glViewport(0, 0, w, h);
}

void Base::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((GLfloat) yoffset);
}

void Base::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
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