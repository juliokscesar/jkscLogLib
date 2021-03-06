/*
* MIT License
* 
* Copyright (c) 2021 juliokscesar
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "../griffinLog.h"

/* 
Compile with:
gcc test_c.c ../griffinLog.c
*/

int main(void)
{
    // Info logging
    grflog_info("hello my name is %s how are you today?", "Julio");

    // Debug logging
    grflog_debug("hello this is a %s debug message in %d", "formatted", 2021);

    // Warn Logging
    grflog_warn("Warning! This is a log warning to you %s", "user");

    // Initialize file logging
    if (!grflog_init_file("logfilename.log"))
        return -1;
    grflog_info("From now, it will log to a file as well!");

    // Critical logging
    grflog_critical("Critical error! Find out today in %d", 2021);

    // Fatal logging
    grflog_fatal("Fatal error! Your pc will die, but it is %s", "just a joke");

    // Finish file logging (needs to be called if you initialized it)
    grflog_finish_file();
    return 0;
}
