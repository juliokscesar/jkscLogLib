# jksc Logging Lib - A Simple Logging Library for C/C++
jksc Logging Lib is a simple logging library just to include the basics of logging info to a file, what you could simply do with no library, but jksc helps by having no need to write every single time.

## Attention
jsksc Logging Lib literally only includes the basics - Init, Write and Finish (and a function to get the datetime).

## Getting Started
To use the jksc Logging Lib, you only need to clone the repository or download the needed files for your programming language. **THIS IS NOT A ADVANCED LIBRARY, ONLY SOMETHING I WROTE TO USE FOR MYSELF AND NO NEED TO WRITE IT EVERY TIME**.
Clone the repository with `git clone https://github.com/juliokscesar/jkscLogLib.git`

### Requirements
#### C
- Log.h
- Log.c

#### C++ (files are in cpp folder)
- Log.hpp
- Log.cpp

## Building
Just `#include "Log.h"` (C) or `#include "Log.hpp"` (C++) in your code and add Log.c (C) or Log.cpp (C++) to compile with your project. C++ files will separate the functions in a namespace and allow you to choose the base file name (currently working in setting custom file name in C).

## Example Code
### C
`#include "../Log.h"

int main()
{
    if (!LogInit())
        return 1;

    LogWriteLine("testing c log line");
    LogWrite("testing c log");

    LogFinish();

    return 0;
}`

### C++
`#include "../cpp/Log.hpp"

int main()
{
    // Initiate with default name
    // Log::Init();

    // Initiate with custom name
    Log::Init("test_log.log");

    std::string name;
    std::cout << "What is your name?\n";
    std::cin >> name;

    // Write with no \n at the end
    Log::Write("Hello, ");

    // Write with \n at the end
    Log::WriteLine(name);

    Log::Finish();
    return 0;
}`