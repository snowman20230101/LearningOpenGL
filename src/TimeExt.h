//
// Created by windy on 2022/9/19.
//

#ifndef LEARNINGOPENGL_TIMEEXT_H
#define LEARNINGOPENGL_TIMEEXT_H


#include <cstdlib>
#include <sys/time.h>

static long long GetSysCurrentTime() {
    struct timeval time;
    gettimeofday(&time, NULL);
    long long curTime = ((long long) (time.tv_sec)) * 1000 + time.tv_usec / 1000;
    return curTime;
}

static const char *getTimeByYMD() {
    time_t current = GetSysCurrentTime() / 1000;
    char s[100];
    tm *p = gmtime(&current); // UTC
    tm *lp = localtime(&current); // CST
    tm tmp = {0};
    // 这里是保护，空指针
    if (p) {
        tmp = *p;
    }

    strftime(s, sizeof(s), "%Y-%m-%d", &tmp);
    return s;
}

static const char *getTimeByHMS(time_t sec) {
    char s[100];
    tm *p = gmtime(&sec); // UTC
    tm *lp = localtime(&sec); // CST
    tm tmp = {0};
    // 这里是保护，空指针
    if (p) {
        tmp = *p;
    }

    if (sec >= 3600) {
        strftime(s, sizeof(s), "%H:%M:%S", &tmp);
    } else {
        strftime(s, sizeof(s), "%M:%S", &tmp);
    }
    return s;
}

#endif //LEARNINGOPENGL_TIMEEXT_H
