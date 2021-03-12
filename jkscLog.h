/*
MIT License

Copyright (c) 2021 juliokscesar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef LOG_H
#define LOG_H

#define ANSI_COLOR_RED     "\x1b[31;1;1m"
#define ANSI_COLOR_GREEN   "\x1b[32;1;1m"
#define ANSI_COLOR_YELLOW  "\x1b[38;2;255;255;1;1m"
#define ANSI_COLOR_BLUE    "\x1b[34;1;1m"
#define ANSI_COLOR_MAGENTA "\x1b[35;1;1m"
#define ANSI_COLOR_CYAN    "\x1b[36;1;1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

typedef enum
{
    INFO     = 0,
    DEBUG    = 1,
    WARN     = 2,
    CRITICAL = 3
} LogMode;

int jkscLogInit();
int jkscLogInitCustom(const char* fileName);
void jkscLogWriteMode(int logMode, char *log);
void jkscLogInfo(const char *logInfo, ...);
void jkscLogDebug(const char *logDebug, ...);
void jkscLogWarn(const char *logWarn, ...);
void jkscLogCritical(const char *logCritical, ...);
int jkscLogFinish();

char *GetCurrentDateTime();

#endif // LOG_H