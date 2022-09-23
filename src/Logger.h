//
// Created by windy on 2022/9/19.
//

#ifndef LEARNINGOPENGL_LOGGER_H
#define LEARNINGOPENGL_LOGGER_H

#include <iostream>

#include "TimeExt.h"
#include "CommonInclude.h"
#include "Def.h"

static const int MAX_LOG_LENGTH = 16 * 1024;

static void Logger(const char *format, va_list args) {
    char buf[MAX_LOG_LENGTH]; // 栈
    timeval now;
    struct tm *time;
    gettimeofday(&now, nullptr);
    time = localtime((&now.tv_sec));

    int len;
    if (time == nullptr) {
        return;
    }

    len = snprintf(buf, sizeof(buf) - 1, "[%02d-%02d-%02d] [%02d:%02d:%02d.%03d][%08lx] ",
                   time->tm_year,
                   time->tm_mon + 1,
                   time->tm_mday,
                   time->tm_hour,
                   time->tm_min,
                   time->tm_sec,
                   int(now.tv_usec / 1000),
                   pthread_self()
    );

    if (len >= 0 && len < sizeof(buf)) {
        vsnprintf(buf + len, sizeof(buf) - len - 1, format, args);
    }

    // 之前的空间应该已经处理好了。
    strcat(buf, "\n");

    std::string logPath(ROOT_DIR);
    std::string path = CC_FORMAT("%s/okay_log_%d_%d.log", logPath.c_str(), time->tm_mon, time->tm_mday);
    FILE *fd = fopen(path.c_str(), "a");
    if (fd) {
        fputs(buf, fd);
        fflush(fd);
        fclose(fd);
    }
    printf("%s\n", buf);
}

static void CCLog(const char *format, ...) {
    va_list args;
    va_start(args, format);
    Logger(format, args);
    va_end(args);
}

#endif //LEARNINGOPENGL_LOGGER_H
