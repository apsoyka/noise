#pragma once
#include <string>

using namespace std;

struct Pixel {
    unsigned char red, green, blue;
};

struct Image {
    Pixel *pixels;
    int width, height, dpi;
};

string &ltrim(string &string, const std::string characters = "\t\n\v\f\r ");

string &rtrim(string &string, const std::string characters = "\t\n\v\f\r ");

string &trim(string &string, const std::string characters = "\t\n\v\f\r ");