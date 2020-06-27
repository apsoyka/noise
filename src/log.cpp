#include <iostream>
#include <map>
#include "log.h"
#include "configuration.h"

static const map<Priority, string> priorities = {
    {ERROR, "ERROR"},
    {WARN, "WARN"},
    {INFO, "INFO"},
    {DEBUG, "DEBUG"},
    {VERBOSE, "VERBOSE"}
};

void Log::error(string tag, string message) {
    println(ERROR, tag, message);
}

void Log::warn(string tag, string message) {
    println(WARN, tag, message);
}

void Log::info(string tag, string message) {
    println(INFO, tag, message);
}

void Log::debug(string tag, string message) {
    #ifndef DEBUG
    println(DEBUG, tag, message);
    #endif
}

void Log::verbose(string tag, string message) {
    if (Configuration::get_verbose())
        println(VERBOSE, tag, message);
}

void Log::println(Priority priority, string tag, string message) {
    cout << priorities.at(priority) << '/' << tag << ": " << message << endl;
}