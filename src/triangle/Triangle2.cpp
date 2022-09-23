//
// Created by windy on 2021/12/16.
// 用 VAO VBO EBO 画四边形，或者说多个三角形
// VAO 顶点数组对象
// VBO 顶点缓冲对象
// EBO 索引缓冲对象
//

#include "Triangle2.h"

Triangle2::Triangle2() {
    std::cout << "Triangle2()" << std::endl;
}

Triangle2::~Triangle2() {
    std::cout << "~Triangle2()" << std::endl;
}

int Triangle2::execute() {
    std::cout << "Triangle2 execute()" << std::endl;
    createWindow();

    unsigned int programId = createGLProgram(triangleVertexFile, triangleFragmentFile);

    unsigned int VAO[2];
    unsigned int VBO[2];
    unsigned int EBO;

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);

    // 第一个
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_1Vertices), triangle_1Vertices, GL_STATIC_DRAW);

    // 这里需要初始化 EBO 索引缓冲对象 TODO 这里必须是先 绑定完 VAO VBO 才能 绑定 EBO。也就是说，必须是以 VAO VBO 在 EBO。顺序不能随意。不然画面出不来。
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 第二个
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_1Vertices2), triangle_1Vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // EBO 绘制
        glBindVertexArray(0);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(programId);

    glfwTerminate();
    return 0;
}