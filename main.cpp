#include <iostream>

#include "Base.h"

#include "Triangle.h"
#include "Triangle2.h"
#include "TriangleExercises_1.h"
#include "TriangleExercises_2.h"
#include "TriangleExercises_3.h"

#include "TexturePicture.h"
#include "TexturePicture_1.h"
#include "TexturePicture_2.h"
#include "TexturePicture_3.h"
#include "TexturePicture_4.h"

#include "GLMSample.h"
#include "GLMSample3D.h"
#include "GLMSample3D36.h"
#include "GLMSample3D36_2.h"

#include "CameraCircle.h"
#include "CameraCircleKeyboard_dt.h"
#include "CameraCircleZoom.h"
#include "CameraCircleZoomClass.h"
#include "CameraCircleAlon.h"

#include "GLColor.h"
#include "TestClass.h"
#include "BeatingHeartSample.h"

#include "CharactersSample.h"

#include "AssimpSample.h"

#include "FBOSample.h"

#include "SphereSample.h"
#include "SphereSample2.h"
#include "SphereSample3.h"
#include "SphereLightSample.h"

#include "TimeExt.h"
#include "Logger.h"

extern "C" {
#include <libavutil/avutil.h>
}

/**
 * OpenGL测试
 *
 * @return
 */
int testOpenGL();

/**
 * 时间 测试方法
 *
 * @return
 */
int printTimeSamp();

/**
 *
 */
void printSii();

int main() {
    const char *version = av_version_info();
    printf("ffmpeg version is %s\n", version);
    (new TestClass())->exampleYaml();

    // openGL 测试用例
//    testOpenGL();

    // 测试时间
//    printTimeSamp();
    return 0;
}

int testOpenGL() {
    std::cout << "Hello welcome learning OpenGL ES!" << std::endl;

    Base *base;
    // 初级顶点
    base = new Base();

//    base = new Triangle();
//    base = new Triangle2();
//    base = new TriangleExercises_1();
//    base = new TriangleExercises_2();
//    base = new TriangleExercises_3();

    // 纹理
//    base = new TexturePicture();
//    base = new TexturePicture_1();
//    base = new TexturePicture_2();
//    base = new TexturePicture_3();
//    base = new TexturePicture_4();

    // 数学GLM，矩阵转换
//    base = new GLMSample();
//    base = new GLMSample3D();
//    base = new GLMSample3D36();
//    base = new GLMSample3D36_2();

    // camera
//    base = new CameraCircle();
//    base = new CameraCircleKeyboard_dt();
//    base = new CameraCircleZoom();
//    base = new CameraCircleZoomClass();
    base = new CameraCircleAlon();

// 光照
//    base = new GLColor();

//    base = new BeatingHeartSample();

    // 绘制文字
//    base = new CharactersSample();

    // 模型加载
//    base = new AssimpSample();

    // FBO
    base = new FBOSample();

    // 球体
//    base = new SphereSample();
//    base = new SphereSample2();
//    base = new SphereSample3();
//    base = new SphereLightSample();

    return base->execute();
}

int printTimeSamp() {
    struct timeval timeValue;
    gettimeofday(&timeValue, 0);

    printf("%ld\n", timeValue.tv_sec); // 当前时间秒
    printf("%d\n", timeValue.tv_usec); // 微妙
    printf("%lld\n", GetSysCurrentTime());

    char s[100];
    struct tm tmp = {0};
    const time_t t = 5394;
    struct tm *p = gmtime(&t);
    if (p) {
        tmp = *p;
    }
    strftime(s, sizeof(s), "%H:%M:%S", &tmp);
    printf("s=%s\n", s);
    printf("s=%s\n", getTimeByHMS(3500));

    struct tm *ptr;
    time_t lt;
    char str[80];
    lt = time(nullptr);
    ptr = localtime(&lt);
    strftime(str, 100, "It is now %I %p", ptr);
    printf("%s", str);


    struct tm *newtime;
    char tmpbuf[128];
    time_t lt2;
    lt2 = time(nullptr);
    newtime = localtime(&lt2);
    strftime(tmpbuf, 128, "Today is %A, day %d of %B in the year %Y.\n", newtime);
    printf("%s", tmpbuf);

    printf("current=%s", getTimeByYMD());
    return 0;
}

void printSii() {
    int str[5] = {1, 2, 3, 5, 6};
    memset(str, 1, sizeof(str));
    std::cout << str[0] << std::endl;
    unsigned int a = str[0];
    for (int i = 31; i >= 0; i--)
        cout << (a >> i & 1);
}