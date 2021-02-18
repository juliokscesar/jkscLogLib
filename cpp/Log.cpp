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

#include "Log.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>

namespace jkscLog
{
    std::ofstream logFile;

    bool Init()
    {
        if (!logFile.is_open())
            logFile.open("logfile.log");

        jkscLog::WriteLine("Log Initiated");
        return logFile.is_open();
    }

    bool Init(const std::string& fileName)
    {
        if (!logFile.is_open())
            logFile.open(fileName);
        
        jkscLog::WriteLine("Log Initiated");
        return logFile.is_open();
    }

    void WriteLine(const std::string& logInfo)
    {
        logFile << "[" << GetDateTimeNow() << "] " << logInfo << "\n";
    }

    void Write(const std::string& logInfo)
    {
        logFile << "[" << GetDateTimeNow() << "] " << logInfo;
    }

    void WriteFormatted(const std::string& formatLog, ...)
    {
        va_list args;
        va_start(args, formatLog);

        const int logSize = (int)formatLog.length() + 256;
        char* log = new char[logSize];

        vsprintf(log, formatLog.c_str(), args);

        Write(log);

        delete[] log;
        va_end(args);
    }

    bool Finish()
    {
        jkscLog::WriteLine("Log Finished");
        
        if (logFile.is_open())
            logFile.close();

        return !logFile.is_open();
    }

    const std::string GetDateTimeNow()
    {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::stringstream stream;
        stream << std::put_time(now, "%Y-%m-%d;%H:%M:%S%p");

        std::string timeNow;
        stream >> timeNow;

        return timeNow;
    }
}