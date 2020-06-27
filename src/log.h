#pragma once
#include <string>

using namespace std;

enum Priority {
    ERROR,
    WARN,
    INFO,
    DEBUG,
    VERBOSE
};

class Log {
    public:
        static void error(string, string);
        static void warn(string, string);
        static void info(string, string);
        static void debug(string, string);
        static void verbose(string, string);
        static void println(Priority, string, string);
};