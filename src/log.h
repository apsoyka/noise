#pragma once

#include <iostream>
#include <string>
#include <map>
#include "configuration.h"

using namespace std;

enum Priority {
    ERROR,
    WARN,
    INFO,
    DEBUG,
    VERBOSE
};

static const map<Priority, string> priorities = {
    {ERROR, "ERROR"},
    {WARN, "WARN"},
    {INFO, "INFO"},
    {DEBUG, "DEBUG"},
    {VERBOSE, "VERBOSE"}
};

class Log {
    public:
        template <typename... Types>
        static void error(string tag, string format, Types... arguments) {
            println(ERROR, tag, format, arguments...);
        }

        template <typename... Types>
        static void warn(string tag, string format, Types... arguments) {
            println(WARN, tag, format, arguments...);
        }

        template <typename... Types>
        static void info(string tag, string format, Types... arguments) {
            println(INFO, tag, format, arguments...);
        }

        template <typename... Types>
        static void debug(string tag, string format, Types... arguments) {
            println(DEBUG, tag, format, arguments...);
        }

        template <typename... Types>
        static void verbose(string tag, string format, Types... arguments) {
            println(VERBOSE, tag, format, arguments...);
        }

        template <typename... Types>
        static void println(Priority priority, string tag, string format, Types... arguments) {
            auto proceed = true;

            if (priority == VERBOSE)
                proceed = Configuration::get_verbose();
            
            if (priority == DEBUG) {
                #ifndef NDEBUG
                proceed = false;
                #endif
            }

            if (proceed) {
                format = priorities.at(priority) + '/' + tag + ": " + format;
                auto buffer = new char[1024];
                snprintf(buffer, 1024, format.c_str(), arguments...);
                cout << buffer << endl;
                delete[] buffer;
            }
        }
};