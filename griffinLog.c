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

#include "griffinLog.h"

#if defined(GRIFFIN_LOG_WIN32)
#include <Windows.h>

void SetConsoleColor(WORD* Attributes, DWORD Color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Color);
}

void ResetConsoleColor(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

#else

#include <sys/stat.h>

#endif // GRIFFIN_LOG_WIN32

// Utility functions

/**
 * Creates a directory if it doesn't exist
 * @param path Path to create the directory.
 */
void make_directory(const char* path)
{
    #if defined(GRIFFIN_LOG_WIN32)
    CreateDirectoryA(path, NULL);
    #else
    mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif // GRIFFIN_LOG_WIN32
}

/**
 * Print the current date and time formatted as yyyy-mm-dd H:M:S to the string dest.
 * @param dest string destination to have the date and time. MINMUM SIZE: 21 bytes.
 */
void strdatetime(char* dest)
{
    time_t t = time(0);
    struct tm now;

    #if defined(GRIFFIN_LOG_WIN32) && defined(_MSC_VER)
    if (localtime_s(&now, &t) != 0)
    {
        perror("Error when getting time: ");
        *dest = '\0';
        return;
    }
    #else
    now = *(localtime(&t));
    #endif // GRIFFIN_LOG_WIN32 && _MSC_VER

    strftime(dest, 20, "%Y-%m-%d %H:%M:%S", &now);
}


// Visual functions (levels as strings and their colors)

/**
 * Get the string that corresponds to the log level lvl.
 * @param lvl Log level enumerated in enum log_level.
 */
const char* get_log_lvl_str(uint32_t lvl)
{
    static const char* levels[] = { "INFO", "DEBUG", "WARN", "CRITICAL", "FATAL" };
    return levels[lvl];
}

/**
 * Get the color that corresponds to the log level lvl. The color is only used on console logging.
 * @param lvl Log level enumerated in enum log_level.
 */
const GRIFFIN_COLOR get_log_lvl_color(uint32_t lvl)
{
    static const GRIFFIN_COLOR level_colors[] = { GRIFFIN_COLOR_BLUE, GRIFFIN_COLOR_GREEN, GRIFFIN_COLOR_YELLOW, GRIFFIN_COLOR_RED, GRIFFIN_COLOR_BLACK_RED };
    return level_colors[lvl];
}


struct log_event
{
    uint32_t lvl;
    char datetime[21];
    const char* log_lvl_str;
    const char* content;
};

void construct_log_event(struct log_event* l_ev, uint32_t log_lvl, const char* what)
{
    l_ev->lvl = log_lvl;
    strdatetime(l_ev->datetime);
    l_ev->log_lvl_str = get_log_lvl_str(log_lvl);
    l_ev->content = what;
}

// File logging functions
static FILE* log_file;
int grflog_init_file(const char* log_file_name)
{
    if (!log_file)
    {
        char log_path[256];
        strcpy(log_path, "./logs/");

        make_directory(log_path);

        strncat(log_path, log_file_name, sizeof(log_path) - strlen(log_file_name));

        log_file = fopen(log_path, "w");
    }

    grflog_info("File logging Initialized");
    return !(log_file == NULL);
}

void grflog_log_file(struct log_event* l_ev)
{
    if (log_file)
        fprintf(log_file, "[%s] [%s] %s\n", l_ev->datetime, l_ev->log_lvl_str, l_ev->content);
}

void grflog_finish_file(void)
{
    grflog_info("File logging Finished");
    if (log_file)
    {
        fflush(log_file);
        fclose(log_file);
    }
}


// Console logging function

void grflog_log_console(struct log_event* l_ev)
{
    const GRIFFIN_COLOR color = get_log_lvl_color(l_ev->lvl);

    #if defined(GRIFFIN_LOG_WIN32)

    printf("[%s] [", l_ev->datetime);

    WORD attributes;
    SetConsoleColor(&attributes, color);
    printf("%s", l_ev->log_lvl_str);
    ResetConsoleColor(attributes);

    printf("] %s\n", l_ev->content);

    #elif defined(GRIFFIN_LOG_LINUX)

    printf("[%s] [%s%s%s] %s\n", l_ev->datetime, color, l_ev->log_lvl_str, GRIFFIN_COLOR_RESET, l_ev->content);

    #endif // GRIFFIN_LOG_WIN32
}


// Main log function
void grflog_log(uint32_t log_lvl, const char* log_fmt, ...)
{
    const size_t log_size = strlen(log_fmt) + 256;
    char log[log_size];

    va_list vaArgs;
    va_start(vaArgs, log_fmt);
    vsnprintf(log, log_size - 1, log_fmt, vaArgs);
    va_end(vaArgs);

    struct log_event l_ev;
    construct_log_event(&l_ev, log_lvl, log);

    grflog_log_console(&l_ev);
    grflog_log_file(&l_ev);
}
