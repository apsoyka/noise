#pragma once

#include <string>

using namespace std;

class Configuration {
    public:
        static bool get_verbose();
        static void set_verbose(bool);
        static int get_width();
        static void set_width(int);
        static int get_height();
        static void set_height(int);
        static int get_dpi();
        static void set_dpi(int);
        static string get_source();
        static void set_source(string);
        static string get_destination();
        static void set_destination(string);
        static bool get_invert();
        static void set_invert(bool);
};