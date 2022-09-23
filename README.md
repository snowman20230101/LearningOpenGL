# LearningOpenGL
this is Clion project.



这是一个Opengl学习Demo。

持续更新中。

1、安装 CLion .以及自行配置c++环境。

2、项目需要配置项：

​	CommonInclude.h 中修改 ROOT_DIR 和 RAW 资源路径。

​    需要修改CmakeList.txt 配置。（需要配置你自己电脑中的相关依赖）

```
# ffmpeg
set(FFMPEG_DIR /usr/local/Cellar/ffmpeg/5.0)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

# 添加头文件
# GL
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
# glfw
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
# freeType
set(FREE_TYPE /usr/local/Cellar/freetype/2.11.1/include)
# freeType 引入头文件异常处理方案
set(FREE_TYPE2 /usr/local/Cellar/freetype/2.11.1/include/freetype2)
# assimp OpenGL 模型
set(ASSIMP /usr/local/Cellar/assimp/5.2.2/include)
# glad
set(GLAD /usr/local/Cellar/glad/include)
# glm
set(GLM /usr/local/Cellar/glm/include)
#yaml-cpp
set(YAML_CPP /usr/local/include/yaml-cpp)

set(SYSTEM /usr/local/include)

include_directories(${GLEW_H} ${GLFW_H} ${ASSIMP} ${FREE_TYPE} ${FREE_TYPE2} ${GLAD} ${GLM} ${FFMPEG_DIR}/include ${SYSTEM})
include_directories(
        src
        src/util
        src/camera
        src/beat_heart
        src/color
        src/glm
        src/texture
        src/triangle
        src/test
        src/assimp
        src/buffer
        src/sphere
        src/geometry
)

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.dylib)
set(FREE_TYPE_LINK /usr/local/Cellar/freetype/2.11.1/lib/libfreetype.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/5.2.2/lib/libassimp.dylib)

link_libraries(${OPENGL} ${GLFW_LINK} ${GLEW_LINK} ${FREE_TYPE_LINK} ${ASSIMP_LINK})

# ffmpeg 必须用这个引入包
link_directories(${FFMPEG_DIR}/lib)

link_directories(/usr/local/lib)

```

这里说明下，ffmpeg 可以去掉。目前还没用到。