cmake_minimum_required(VERSION 3.21)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 14)

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
#yaml-cpp 文件解析
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

message("called main cmakeLists.txt")

# 执行编译命令
set(SOURCE_FILE
        src/glad.c
        src/util/Utils.cpp
        main.cpp
        src/util/stb_image.cpp
        src/CommonInclude.cpp
        src/Base.cpp
        src/triangle/Triangle.cpp
        src/triangle/Triangle2.cpp
        src/triangle/TriangleExercises_1.cpp
        src/triangle/TriangleExercises_2.cpp
        src/triangle/TriangleExercises_3.cpp
        src/texture/TexturePicture.cpp
        src/texture/TexturePicture_1.cpp
        src/texture/TexturePicture_2.cpp
        src/texture/TexturePicture_3.cpp
        src/texture/TexturePicture_4.cpp
        src/glm/GLMSample.cpp
        src/glm/GLMSample3D.cpp
        src/glm/GLMSample3D36.cpp
        src/camera/CameraCircle.cpp
        src/camera/CameraCircleKeyboard_dt.cpp
        src/camera/CameraCircleZoom.cpp
        src/camera/CameraCircleZoomClass.cpp
        src/color/GLColor.cpp
        src/test/TestClass.cpp
        src/beat_heart/BeatingHeartSample.cpp
        src/glm/GLMSample3D36_2.cpp
        src/beat_heart/CharactersSample.cpp
        src/assimp/AssimpSample.cpp
        src/assimp/Mesh.cpp
        src/assimp/Model.cpp
        src/buffer/FBOSample.cpp
        src/sphere/SphereSample.cpp
        src/sphere/SphereSample2.cpp
        src/sphere/Sphere.cpp
        src/sphere/SphereSample3.cpp
        src/sphere/SphereLightSample.cpp
        src/geometry/GeometrySample.cpp
        src/geometry/GeometrySample.h
        src/camera/CameraCircleAlon.cpp src/camera/CameraCircleAlon.h)

add_executable(LearningOpenGL ${SOURCE_FILE})

target_link_libraries(
        LearningOpenGL
        swscale swresample avcodec avutil avdevice avfilter avformat yaml-cpp
)

if (APPLE)
    target_link_libraries(LearningOpenGL "-framework OpenGL")
    target_link_libraries(LearningOpenGL "-framework GLUT")
endif ()
