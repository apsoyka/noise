#pragma once

#include <string>

using std::string;

class Configuration {
    public:
        static void parse(int, char *[]);
        static bool get_verbose();
        static int get_width();
        static int get_height();
        static int get_dpi();
        static string get_source();
        static string get_destination();
        static bool get_invert();
        static bool get_compression();
};