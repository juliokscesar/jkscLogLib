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

#ifndef JKSCLOG_H
#define JKSCLOG_H

#if defined(WIN32) || defined(_WIN32)
    #define COLOR_RED       0x0c
    #define COLOR_GREEN     0x0a
    #define COLOR_BLUE      0x09
    #define COLOR_YELLOW    0x0e
#else
    #define COLOR_RED     "\x1b[31;1;1m"
    #define COLOR_GREEN   "\x1b[32;1;1m"
    #define COLOR_BLUE    "\x1b[34;1;1m"
    #define COLOR_YELLOW  "\x1b[38;2;255;255;1;1m"
    #define COLOR_RESET   "\x1b[0m"
#endif // WIN32 || _WIN32

#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <exception>

namespace jkscLog
{
    enum LogMode
    {
        INFO     = 0,
	    DEBUG    = 1,
        WARN     = 2,
        CRITICAL = 3
    };

    bool Init();
    bool Init(const std::string &logFileName);

    void LogWriteMode(LogMode logMode, const std::string &log);
    void LogWriteModeConsole(LogMode logMode, const std::string &log);

    void Info(const std::string &logInfo, ...);
    void Debug(const std::string &logDebug, ...);
    void Warn(const std::string &logWarn, ...);
    void Critical(const std::string &logCritical, ...);

    bool Finish();

    const std::string GetDateTimeNow();
}

#endif // JKSCLOG_H
