//
// Created by windy on 2021/12/16.
// 结合 VAO VBO 画三角形
// VAO 顶点数组对象
// VBO 顶点缓冲对象
//

#include "Triangle.h"

Triangle::Triangle() {
    std::cout << "Triangle Triangle()" << std::endl;
}

Triangle::~Triangle() {
    std::cout << "Triangle ~Triangle()" << std::endl;
}

int Triangle::execute() {
    std::cout << "Triangle execute()" << std::endl;

    // 创建窗口
    createWindow();

    // 创建 GL Program 【顶点着色器，片元着色器】
    unsigned int programId = createGLProgram(triangleVertexFile, triangleFragmentFile);
//    unsigned int programId2 = createGLProgram(beatingHeartVertexFile, beatingHeartFragmentFile);
//    std::cout << "programId2=" << programId2 <<  std::endl;

    // TODO 步骤1：定义 两个对象

    // 定义 VAO 对象
    unsigned int VAO; // 顶点数组对象(Vertex Array Object, VAO)
    // 定义 VBO 对象
    unsigned int VBO; // 顶点缓冲对象(Vertex Buffer Objects, VBO)

    // TODO 步骤2：创建对象，其实叫申请内存

    // 创建一个顶点数组对象
    // 第一个参数：需要创建的缓存数量
    // 第二个参数：存储单一ID或多个ID的GLuint变量或数组的地址
    glGenVertexArrays(1, &VAO);

    // 创建一个顶点缓冲对象。
    // 第一个参数：需要创建的缓存数量
    // 第二个参数：存储单一ID或多个ID的GLuint变量或数组的地址
    glGenBuffers(1, &VBO);

    // TODO 步骤3：相当于初始化内存

    // 顶点数组对象创建之后，在使用缓存对象之前，需要将缓存对象连接到相应的缓存上。
    // glBindBuffer()有1个参数：buffer。（绑定和解绑的顺序很重要，勿更改）
    glBindVertexArray(VAO);

    // 顶点缓存对象创建之后，在使用缓存对象之前，需要将缓存对象连接到相应的缓存上。
    // glBindBuffer()有2个参数：target与buffer。（绑定和解绑的顺序很重要，勿更改）
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 当缓存初始化之后，使用glBufferData()将顶点数据拷贝到缓存对象（VBO）
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    // TODO 步骤4：解释顶点数据

    // 设置顶点属性指针，glVertexAttribPointer()函数告诉OpenGL该如何解析顶点数据
    // 顶点属性位置 0 是顶点，1 是颜色（着色器）
    // 顶点属性大小 3 （vec3）
    // 数据的类型 顶点数据通常都是 float
    // 是否被标准化 定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
    // 步长 因为跨一个点点和颜色才是下一个vec3 所以 步长是 6 * float
    // 偏移 对于顶点不需要偏移，因为一开始就是 顶点坐标数据了。 对于颜色需要偏移3 * float，因为3个点点后才是颜色
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    // 以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TODO 步骤5：这里先需要解绑

    // 解绑缓存着色器（绑定和解绑的顺序很重要，勿更改）
    // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 解绑顶点着色器（绑定和解绑的顺序很重要，勿更改）
    glBindVertexArray(0);  // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    // render loop
    // ------------------------------
    while (!glfwWindowShouldClose(pWindow)) {
        // input
        processInput(pWindow);
        // TODO 步骤6：开始绘制
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(programId);
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindVertexArray(VAO);

        // 线框模式(Wireframe Mode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE
        glDrawArrays(GL_TRIANGLES, 0, 3); // glDrawArrays的功能：提供绘制功能，从数组数据中提取数据渲染基本图元。
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.) 交换数据
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programId);

    glfwTerminate();
    return 0;
}

/**
* GL_POINTS：把每一个顶点作为一个点进行处理，顶点n即定义了点n，共绘制N个点
* GL_LINES：连接每两个顶点作为一个独立的线段，顶点2n－1和2n之间共定义了n条线段，总共绘制N/2条线段
* GL_LINE_STRIP：绘制从第一个顶点到最后一个顶点依次相连的一组线段，第n和n+1个顶点定义了线段n，总共绘制n－1条线段
* GL_LINE_LOOP：绘制从第一个顶点到最后一个顶点依次相连的一组线段，然后最后一个顶点和第一个顶点相连，第n和n+1个顶点定义了线段n，总共绘制n条线段
* GL_TRIANGLES：把每三个顶点作为一个独立的三角形，顶点3n－2、3n－1和3n定义了第n个三角形，总共绘制N/3个三角形
* GL_TRIANGLE_STRIP：绘制一组相连的三角形，对于奇数n，顶点n、n+1和n+2定义了第n个三角形；对于偶数n，顶点n+1、n和n+2定义了第n个三角形，总共绘制N-2个三角形
* GL_TRIANGLE_FAN：绘制一组相连的三角形，三角形是由第一个顶点及其后给定的顶点确定，顶点1、n+1和n+2定义了第n个三角形，总共绘制N-2个三角形
*/