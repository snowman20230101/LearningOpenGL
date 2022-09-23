//
// Created by windy on 2022/9/19.
//

#ifndef LEARNINGOPENGL_DEF_H
#define LEARNINGOPENGL_DEF_H

#include <iostream>

// 格式化字符串
// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
std::string CC_FORMAT(const char *fmt, ...) {
    int size = 1024;

    std::string str;
    va_list ap;
    for (int j = 0; j < 8; ++j) {     // Maximum two passes on a POSIX system...
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *) str.data(), size, fmt, ap);
        va_end(ap);
        if (n >= 0 && n < size) {  // Everything worked
            str.resize(n);
            return str;
        }
        if (n > -1)  // Needed size returned
            size = n + 1;   // For null char
        else
            size = (j + 1) * 32 * 1024;      // Guess at a larger size (OS specific)
    }

    str.clear();
    return str;
}

#endif //LEARNINGOPENGL_DEF_H
